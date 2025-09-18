#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>

struct Persona {
  int             id;
  std::string     nombre;
  int             edad;
  std::string     ciudad;
  struct {
    struct {
      std::string   email;
      std::string   telefono;
    } contacto;
    struct {
      std::string puesto;
      std::string empresa;
    } empleo;
  } detalles;
};

void print_persona(Persona& persona)
{
  std::cout << "ID: "     << persona.id << "\n"
            << "Edad: "   << persona.edad << "\n"
            << "Ciudad: " << persona.ciudad << "\n"
            << "Detalles:\n"
            << "\tContacto:\n"
            << "\t\tEmail: "    << persona.detalles.contacto.email << "\n"
            << "\t\tTelefono: " << persona.detalles.contacto.telefono << "\n"
            << "\tEmpleo:\n"
            << "\t\tPuesto: "   << persona.detalles.empleo.puesto << "\n"
            << "\t\tEmpresa: "  << persona.detalles.empleo.empresa << std::endl;
}

Persona parse_json(std::string group)
{
  std::string regex_pattern = R"delim(\{\s*"id":\s*(\d*),\s*"nombre":\s*"([\w\sáéíóúñ]*)",\s*"edad":\s(\d+),\s*"ciudad":\s"([\w\sáéíóúñ]*)",\s*"detalles":\s\{((?:.*\s)*)\}\s*\})delim";
  std::smatch matches;
  std::regex pattern(regex_pattern);

  std::regex_match(group, matches, pattern);
  
  Persona persona;
  std::string temp;

  temp = matches[1];
  persona.id = stoi(temp);
  
  persona.nombre = matches[2];
  
  temp = matches[3];
  persona.edad = stoi(temp);

  persona.ciudad = matches[4];

  std::string detalles = matches[5];
  std::cout << matches[5] << std::endl;

  std::smatch matches_detalles;
  std::regex pattern_detalles(R"delim("contacto":\s\{((?:.*\n)*)\s*\},\s*"empleo":\s\{((?:.*\n)*)\s*\})delim");
  std::regex_match(detalles, matches_detalles, pattern_detalles);

  std::cout << matches_detalles.size() << std::endl;
  std::cout << matches_detalles[0] << std::endl;
  std::cout << matches_detalles[1] << " <-1-2-> " << matches_detalles[2] << std::endl;
  std::string contacto = matches_detalles[1];
  std::string empleo = matches_detalles[2];

  std::smatch matches_contacto;
  std::regex pattern_contacto(R"delim(\s*"email":\s"([\w\.\@]*)",\s*"telefono":\s"([\d\-]*)")delim");
  std::regex_match(contacto, matches_contacto, pattern_contacto);

  std::cout << matches_contacto[1] << " <-1-2-> " << matches_contacto[2] << std::endl;
  persona.detalles.contacto.email = matches_contacto[1];
  persona.detalles.contacto.telefono = matches_contacto[2];

  std::smatch matches_empleo;
  std::regex pattern_empleo(R"delim(\s*"puesto":\s"([\w\sáéíóúñ\s]*)",\s*"empresa":\s"([\w\sáéíóúñ\s]*)")delim");
  std::regex_match(empleo, matches_empleo, pattern_empleo);

  std::cout << matches_empleo[1] << " <-1-2-> " << matches_empleo[2] << std::endl;
  persona.detalles.empleo.puesto = matches_empleo[1];
  persona.detalles.empleo.empresa = matches_empleo[2];

  return persona;
}


int main() {
  std::ifstream archivo("personas.json");
  std::string json = "";

  std::string line;
  while (getline(archivo, line))
  {
    json += line + "\n";
  }

  archivo.close();

  std::vector<Persona> personas;
  
  std::smatch matches;
  std::string regex_pattern = R"delim(\[?\s*(\{\s*.*,\s*.*,\s*.*,\s*.*,\s*.*\{?\s*.*\{?\s*.*,?\s*.*\s*\}?,?\s*.*\{?\s*.*,?\s*.*\s*\}?\s*\}?\s*\}),?\s*((?:.*\s)*))delim";
  std::regex pattern(regex_pattern);
  
  int i = 0;
  while (std::regex_match(json, matches, pattern) && i==0)
  {
    std::string match = matches[1];
    personas.push_back(parse_json(match));
    json = std::regex_replace(json, pattern, "$2");
    i++;
  }

  /*
  for (int j = 0; j < personas.size(); j++)
  {
    print_persona(personas[j]);
  }
  */
}
