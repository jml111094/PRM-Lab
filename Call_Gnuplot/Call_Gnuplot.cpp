#include <stdio.h>
#include "stdafx.h"
#include <iostream>

FILE *gnupipe = _popen("\"D:\\Users\\Ampere\\Documents\\PRM-Lab\\bin\\gnuplot.exe\" -persist", "w");					//Pipe zu Gnuplot öffnen
int direct_plot = 0;																									//Schalter-Variable deklarieren
																																						
void direct();																											//Unterprogramm für direkte Ausgabe
void png();																												//Unterprogramm für Ausgabe als PNG


void direct()
{
	//************************Befehle für Gnuplot*********************************//
	fprintf(gnupipe, "cd 'D:\\Users\\Ampere\\Documents\\PRM-Lab\\Call_Gnuplot'\n");										//Pfad angeben
	fprintf(gnupipe, "set title 'Spannungswerte'\n");																	//Titel definieren
	fprintf(gnupipe, "set ylabel 'Spannung [V]'\n");																	//Y-Achse definieren
	fprintf(gnupipe, "set xlabel 'Messwert n'\n");																		//X-Achse definieren
	fprintf(gnupipe, "unset key \n");
	fprintf(gnupipe, "plot 'Messung2.log' with linespoints pointtype 7 lc rgb 'red' \n");								//Logdatei mit Optionen plotten
	fflush(gnupipe);																									//gesamten Datenstrom an Gnuplot übertragen
	_pclose(gnupipe);																									//Pipe zu Gnuplot schließen

	//************************Keystroke abwarten**********************************//
#ifdef _WIN32
	std::cout << "Gnuplot geschlossen.\nZum Beenden <ENTER> druecken." << std::endl;									//Keystroke abfragen, damit Gnuplot unter Windows geöffnet bleibt
	std::cin.get();
#endif
}

void png()
{
	fprintf(gnupipe, "cd 'D:\\Users\\Ampere\\Documents\\PRM-Lab\\Call_Gnuplot'\n");
	fprintf(gnupipe, "set title 'Spannungswerte'\n");
	fprintf(gnupipe, "set ylabel 'Spannung [V]'\n");
	fprintf(gnupipe, "set xlabel 'Messwert n'\n");
	fprintf(gnupipe, "unset key \n");
	fprintf(gnupipe, "set terminal png \n");
	fprintf(gnupipe, "set output 'Messung.png' \n");																	//Plot als png-Datei speichern
	fprintf(gnupipe, "plot 'Messung2.log' with linespoints pointtype 7 lc rgb 'red' \n");
	fflush(gnupipe);
	_pclose(gnupipe);

	std::cout << "Plot wurde gespeichert.\nZum Beenden <ENTER> druecken." << std::endl;
	std::cin.get();
}

int main()
{
	if (!gnupipe)																										//Abfragen, ob erfolgreich
	{
		return 1;
	}
	
	if (direct_plot == 1)																								//Überprüfung des Schalters
	{
		direct();																																	
	}
	else
	{
		png();
	}

	return 0;
}