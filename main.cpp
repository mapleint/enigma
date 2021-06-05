#include <iostream>

#ifdef _DEBUG
#define printdbg(fmt, x) printf(fmt, x)
#else
#define printdbg(fmt, ...) 
#endif

struct rotor {
	rotor(char* x) 
	{
		memcpy(data, x, 26);
	}

	char shift(char x)
	{
		return data[(x - 'a' + position) % 26];
	}

	char reverse(char x) 
	{
		for (int i = 0; i < 26; i++) {
			if (data[i] == x) {
				return 'a' + i;
			}
		}
		return 0;
	}
	char data[26];
	unsigned char position = 0;
};



class enigma {
public:
	rotor *rotors[3];
	
	struct pair {
		char swap(char x) {
			if (x == A) {
				return B;
			}
			else if (x == B) {
				return A;
			}
			return -1;
		}
		char A = 0;
		char B = 0;
	};

	pair plugboard[10];

	pair reflector[13] = { {'a', 'e'},{'b', 'j'},{'c', 'm'},{'d', 'z'},{'f', 'l'},{'g', 'y'},{'h', 'x'},{'i', 'v'},{'k', 'w'},{'n','r'},{'o','q'},{'p','u'},{'s','t'} };

	


	char type(char in)
	{

		in = tolower(in);

		printdbg("input: %c\n", in);

		/* Go through the plugboard once*/
		for (pair x : plugboard) {
			if (x.A == in || x.B == in)
				in = x.swap(in);
		}

		printdbg("plug out: %c\n", in);

		/* Go through the rotors */
		in = rotors[2]->shift(
			rotors[1]->shift(
				rotors[0]->shift(in)));

		printdbg("rotors: %c\n", in);

		/* Get reflected*/
		for (pair x : reflector) {
			if(x.A == in || x.B == in)
				in = x.swap(in);
		}

		printdbg("reflected: %c\n", in);

		/* Undo what the rotors did*/
		in = rotors[0]->reverse(rotors[1]->reverse(rotors[2]->reverse(in)));

		printdbg("rotor out: %c\n", in);

		for (pair x : plugboard) {
			if (x.A == in || x.B == in)
				in = x.swap(in);
		}

		printdbg("result: %c\n", in);

		/* increment the rotors */
		update_rotor();
		return in;
	}

	void update_rotor()
	{
		rotors[0]->position++;
		if (rotors[0]->position > 25) {
			rotors[0]->position = 0;
			rotors[1]->position++;
			if (rotors[1]->position > 25) {
				rotors[1]->position = 0;
				rotors[2]->position++;
				rotors[2]->position %= 26;
			}
		}
		printf("%i,%i,%i\n", rotors[0]->position, rotors[1]->position, rotors[2]->position);
	}
};



int main() 
{
	char in = 'a';
	rotor A((char*)"ekmflgdqvzntowyhxuspaibrcj");
	rotor B((char*)"ajdksiruxblhwtmcqgznpyfvoe");
	rotor C((char*)"ocresmintvhlaqwfgpykjuxdbz");
	rotor D((char*)"wuervdktmjzpiqasfgybclnxho");
	rotor E((char*)"fnagjucolirpxtmyevwsdhqbkz");


	enigma enigma_machine;
	enigma_machine.rotors[0] = &A;
	enigma_machine.rotors[1] = &B;
	enigma_machine.rotors[2] = &C;


}




