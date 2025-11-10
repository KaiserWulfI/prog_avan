#include <algorithm>
#include <cstdio>
#include <exception>
#include <iostream>
#include <numeric>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

#include <ncurses.h>

namespace {

constexpr int kBoardSize = 4;
constexpr int kTotalTiles = kBoardSize * kBoardSize;
constexpr int kMaxDebugMessages = 5;
constexpr int kBoardTopRow = 3;

bool g_debug_enabled = false;
bool g_ncurses_ready = false;
std::vector<std::string> g_debug_messages;

class NcursesGuard {
public:
    NcursesGuard() {
        if (initscr() == nullptr) {
            throw std::runtime_error("No se pudo iniciar ncurses.");
        }
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        curs_set(0);
        set_escdelay(25);
        g_ncurses_ready = true;
    }

    NcursesGuard(const NcursesGuard&) = delete;
    NcursesGuard& operator=(const NcursesGuard&) = delete;

    NcursesGuard(NcursesGuard&&) = delete;
    NcursesGuard& operator=(NcursesGuard&&) = delete;

    ~NcursesGuard() {
        endwin();
        g_ncurses_ready = false;
    }
};

void debug_log(const std::string& msg) {
    if (!g_debug_enabled) {
        return;
    }

    if (!g_ncurses_ready) {
        std::cerr << "[DEBUG] " << msg << '\n';
    }

    g_debug_messages.push_back(msg);
    if (g_debug_messages.size() > kMaxDebugMessages) {
        g_debug_messages.erase(g_debug_messages.begin());
    }
}

std::vector<int> generate_board() {
    std::vector<int> board(kTotalTiles);
    std::iota(board.begin(), board.end(), 0);

    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(board.begin(), board.end(), rng);

    debug_log("Tablero inicial generado.");
    return board;
}

chtype cast_char(unsigned char ch) {
    return static_cast<chtype>(ch);
}

void print_horizontal_border(int row, unsigned char left, unsigned char middle, unsigned char right) {
    move(row, 0);
    addch(cast_char(left));
    for (int col = 0; col < kBoardSize; ++col) {
        addch(cast_char(205)); // ═
        addch(cast_char(205));
        addch(cast_char(205));
        if (col < kBoardSize - 1) {
            addch(cast_char(middle));
        }
    }
    addch(cast_char(right));
}

void print_board(const std::vector<int>& board, int moves) {
    const unsigned char top_left = 201;    // ╔
    const unsigned char top_sep = 203;     // ╦
    const unsigned char top_right = 187;   // ╗
    const unsigned char mid_left = 204;    // ╠
    const unsigned char mid_sep = 206;     // ╬
    const unsigned char mid_right = 185;   // ╣
    const unsigned char bottom_left = 200; // ╚
    const unsigned char bottom_sep = 202;  // ╩
    const unsigned char bottom_right = 188;// ╝
    const unsigned char vertical = 186;    // ║

    erase();
    mvprintw(0, 0, "Usa flechas o WASD para mover, 'q' para salir.");
    mvprintw(1, 0, "Movimientos realizados: %d", moves);

    const int base_row = kBoardTopRow;
    print_horizontal_border(base_row, top_left, top_sep, top_right);
    for (int row = 0; row < kBoardSize; ++row) {
        int display_row = base_row + 1 + row * 2;
        move(display_row, 0);
        addch(cast_char(vertical));
        for (int col = 0; col < kBoardSize; ++col) {
            int value = board[row * kBoardSize + col];
            if (value == 0) {
                addstr("   ");
            } else {
                char buffer[4];
                std::snprintf(buffer, sizeof(buffer), "%2d ", value);
                addstr(buffer);
            }
            addch(cast_char(vertical));
        }
        if (row < kBoardSize - 1) {
            print_horizontal_border(display_row + 1, mid_left, mid_sep, mid_right);
        }
    }
    print_horizontal_border(base_row + kBoardSize * 2, bottom_left, bottom_sep, bottom_right);

    if (g_debug_enabled) {
        int log_row = base_row + kBoardSize * 2 + 2;
        mvprintw(log_row, 0, "Debug (ultimos %d mensajes):", kMaxDebugMessages);
        clrtoeol();
        int entry_row = log_row + 1;
        for (const auto& msg : g_debug_messages) {
            mvprintw(entry_row, 0, "%s", msg.c_str());
            clrtoeol();
            ++entry_row;
        }
        for (; entry_row < log_row + 1 + kMaxDebugMessages; ++entry_row) {
            move(entry_row, 0);
            clrtoeol();
        }
    }

    refresh();
}

bool is_solved(const std::vector<int>& board) {
    for (int i = 0; i < kTotalTiles - 1; ++i) {
        if (board[i] != i + 1) {
            return false;
        }
    }
    return board.back() == 0;
}

enum class Move {
    None,
    Up,
    Down,
    Left,
    Right,
    Quit
};

Move decode_input() {
    int ch = getch();
    switch (ch) {
        case 'q':
        case 'Q':
            return Move::Quit;
        case 'w':
        case 'W':
            return Move::Up;
        case 's':
        case 'S':
            return Move::Down;
        case 'a':
        case 'A':
            return Move::Left;
        case 'd':
        case 'D':
            return Move::Right;
        case KEY_UP:
            return Move::Up;
        case KEY_DOWN:
            return Move::Down;
        case KEY_LEFT:
            return Move::Left;
        case KEY_RIGHT:
            return Move::Right;
        default:
            return Move::None;
    }
}

bool apply_move(std::vector<int>& board, Move move) {
    if (move == Move::None || move == Move::Quit) {
        return false;
    }

    int zero_index = -1;
    for (int i = 0; i < kTotalTiles; ++i) {
        if (board[i] == 0) {
            zero_index = i;
            break;
        }
    }

    if (zero_index == -1) {
        throw std::runtime_error("El tablero no contiene espacio vacío.");
    }

    int row = zero_index / kBoardSize;
    int col = zero_index % kBoardSize;
    int target_index = zero_index;

    switch (move) {
        case Move::Up:
            if (row > 0) {
                target_index = zero_index - kBoardSize;
            } else {
                return false;
            }
            break;
        case Move::Down:
            if (row < kBoardSize - 1) {
                target_index = zero_index + kBoardSize;
            } else {
                return false;
            }
            break;
        case Move::Left:
            if (col > 0) {
                target_index = zero_index - 1;
            } else {
                return false;
            }
            break;
        case Move::Right:
            if (col < kBoardSize - 1) {
                target_index = zero_index + 1;
            } else {
                return false;
            }
            break;
        default:
            return false;
    }

    debug_log("Movimiento aplicado. Intercambio " + std::to_string(board[target_index]) + " con el espacio vacío.");
    std::swap(board[zero_index], board[target_index]);
    return true;
}

int message_row_position() {
    int row = kBoardTopRow + kBoardSize * 2 + 2;
    if (g_debug_enabled) {
        row += kMaxDebugMessages + 1;
    }
    return row;
}

} // namespace

int main(int argc, char* argv[]) {
    try {
        for (int i = 1; i < argc; ++i) {
            std::string arg(argv[i]);
            if (arg == "--debug" || arg == "-d") {
                g_debug_enabled = true;
            }
        }

        NcursesGuard ncurses_guard;
        auto board = generate_board();
        int moves = 0;
        print_board(board, moves);

        while (true) {
            Move move = decode_input();
            if (move == Move::Quit) {
                int message_row = message_row_position();
                mvprintw(message_row, 0, "Juego terminado por el usuario. Presiona cualquier tecla para salir.");
                refresh();
                getch();
                break;
            }

            if (apply_move(board, move)) {
                ++moves;
                print_board(board, moves);
                if (is_solved(board)) {
                    print_board(board, moves);
                    int message_row = message_row_position();
                    mvprintw(message_row, 0, "Has resuelto el juego en %d movimientos. Presiona cualquier tecla para salir.", moves);
                    refresh();
                    getch();
                    break;
                }
            }
        }
    } catch (const std::exception& ex) {
        std::cerr << "\n[ERROR] Ocurrió una excepción: " << ex.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "\n[ERROR] Ocurrió un error desconocido.\n";
        return 1;
    }

    return 0;
}
