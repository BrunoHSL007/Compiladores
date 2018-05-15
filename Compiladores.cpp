/*
 * Compiladores.cpp
 * 
 * Copyright 2018 BrunoHSL <brunohsl007@brunohsl007-desktop>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <regex.h>
using namespace std;

//const char* RegexID = "[a-zA-Z][a-zA-Z0-9_]*";
//const char* RegexInteiro = "[0-9]+";
//const char* RegexFlutuante = "[0-9]+,[0-9]+";

//string LetrasPermitidas = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
//string NmrsPermitidos = "0123456789";



int main(int argc, char **argv)
{
	//int tam=strlen(argv[1]);
	FILE *input =fopen(argv[1], "r");
	int ContLinha=1; //contador da linha onde está o erro
	//for(int i=0;i<tam;i++){
	
	if (input == NULL)  // Se houve erro na abertura
	{
		printf("Problemas na abertura do arquivo\n");
		return 1;
	}
	int contador=0;
	while (!feof(input))
	{
		// Lê caracter por caracter do arquivo
		char lido = getc(input);
		
		cout << " valor lido["<< contador <<"] = " << lido<< endl;
		
		//Operadores Lógicos
		if(lido=='&')
		{
			lido = getc(input);
			if(lido=='&'){
				cout << "AND" << endl;
			}
			else{
				cout << "Erro na Linha " << ContLinha << " = &" << lido;
				fseek(input, -1, 1); //Volta um caractere
				
			}
		}
		else if(lido=='|')
		{
			lido = getc(input);
			if(lido=='|'){
				cout << "OR" << endl;
			}
			else{
				cout << "Erro na Linha " << ContLinha << " = &" << lido;
				fseek(input, -1, 1); //Volta um caractere
			}
		}
		else if(lido=='=')
		{
			lido = getc(input);
			if(lido=='='){
				cout << "IGUALDADE" << endl;
			}
			else{
				cout << "ATRIBUICAO" << endl;
				fseek(input, -1, 1); //Volta um caractere
			}
		}
		else if(lido=='!')
		{
			lido = getc(input);
			if(lido=='='){
				cout << "DIFERENTE" << endl;
			}
			else{
				cout << "NOT" << endl;
				fseek(input, -1, 1); //Volta um caractere
			}
		}
		else if(lido=='<')
		{
			lido = getc(input);
			if(lido=='='){
				cout << "MENORIGUAL" << endl;
			}
			else{
				cout << "MENOR" << endl;
				fseek(input, -1, 1); //Volta um caractere
			}
		}
		else if(lido=='>')
		{
			lido = getc(input);
			if(lido=='='){
				cout << "MAIORIGUAL" << endl;
			}
			else{
				cout << "MAIOR" << endl;
				fseek(input, -1, 1); //Volta um caractere
			}
		}
		//Controle
		else if(lido=='(')
		{
			cout << "ABREPAR" << endl;
		}
		else if(lido==')')
		{
			cout << "FECHAPAR" << endl;
		}
		else if(lido=='{')
		{
			cout << "ABRECHAVE" << endl;
		}
		else if(lido=='}')
		{
			cout << "FECHACHAVE" << endl;
		}
		else if(lido==';')
		{
			cout << "FIMCOMANDO" << endl;
		}
		//Operadores Aritméticos
		else if(lido=='+')
		{
			cout << "SOMA" << endl;
		}
		else if(lido=='-')
		{
			cout << "SUBTRACAO" << endl;
		}
		else if(lido=='*')
		{
			cout << "MULTIPLICACAO" << endl;
		}
		else if(lido=='/')
		{
			lido = getc(input);
			if(lido=='/'){ //Ignora comentários
				while(getc(input)!='\n');
			}
			else{
				cout << "DIVISAO" << endl;
			}
		}
		//Identificadores
		//else{
		//	string a;
		//	do{
		//		a=getc(input);
		//		cout << "a";
		//	}
		//	while(LetrasPermitidas.substr(a,1));
		//}
		
		
		contador++;
	}
	fclose(input);
	return 0;
}

