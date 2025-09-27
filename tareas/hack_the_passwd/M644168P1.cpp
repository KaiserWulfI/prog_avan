/*
You have been given a special mission in a simulation game: to hack users’ passwords. Somehow, you have obtained the list of usernames, along with the “method” used to generate passwords from these usernames.

The known details are as follows:

Usernames consist only of uppercase letters and are no longer than 20 characters. Additionally, no user uses any letter more than once in their username.

The password for a given username is generated from the 21 consecutive lexicographical permu-tations of that username, with the original username positioned at the 11th (middle) position in this sequence.

For example, if the username is JORGE, the 21 consecutive lexicographical permutations surround-ing JORGE (with JORGE in the middle) would be, in order:

..., JGERO, JGOER, JGORE, JGREO, JGROE, JOEGR, JOERG, JOGER, JOGRE, JOREG, JORGE,

JREGO, JREOG, JRGEO, JRGOE, JROEG, JROGE, OEGJR, OEGRJ, OEJGR, OEJRG, ...

The password is then determined by selecting the permutation among these 21 consecutive lexi-cographical permutations of the username that has the greatest minimum absolute distance between consecutive letters.
In case of a tie, the lexicographically smallest permutation is chosen. Finally, the numerical value of that minimum absolute distance is appended to the selected permutation. Thus, for the username JORGE, the password is JREOG8.

Input

The input consists of a list of usernames. You will have to read until the end of the file.

Output

For each username, print a line containing the password for that username.



Sample Input

JORGE

CARLOS

POMARES

Sample Output

JREOG8

CALROS2

POERSAM1
*/

#include <iostream>

std::string find_password()
{
  //TODO: lexicographical representations down 10 - up 10
  //TODO: Find greatest minimum absolute distance between consecutive letters
  //TODO: In case of tie the lexicographically smallest permutation is chosen
  //TODO: Numerical value of minimum absolute distance appended to permutation.
}

int main()
{
  //TODO: Read from file
  std::string username;

  std::cin >> username;


  //TODO: find_password
}
