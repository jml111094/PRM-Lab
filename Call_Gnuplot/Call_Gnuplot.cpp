#include <stdio.h>
#include "stdafx.h"
#include <iostream>

int main()
{
	FILE *gnupipe = _popen("\"C:\\Users\\Julian\\OneDrive\\Studium BMT\\Praktikum\\PRM Lab\\Call_Gnuplot\\bin\\gnuplot.exe\" -persist", "w");		//Pipe zu Gnuplot öffnen
	if (!gnupipe)																																		//Abfragen, ob erfolgreich
	{
		std::cout << "Gnuplot konnte nicht aufgerufen werden." << std::endl;
	}
	else
	{
		//************************Befehle für Gnuplot*********************************//
		fprintf(gnupipe, "cd 'C:\\Users\\Julian\\OneDrive\\Studium BMT\\Praktikum\\PRM Lab\\Call_Gnuplot\\Call_Gnuplot'\n");							//Pfad angeben
		fprintf(gnupipe, "set title 'Spannungswerte'\n");																								//Titel definieren
		fprintf(gnupipe, "set ylabel 'Spannung [V]'\n");																								//Y-Achse definieren
		fprintf(gnupipe, "set xlabel 'Messwert n'\n");																									//X-Achse definieren
		fprintf(gnupipe, "unset key \n");
		//fprintf(gnupipe, "set terminal png \n");
		//fprintf(gnupipe, "set output 'plot.png' \n");																									//Plot als png-Datei speichern
		fprintf(gnupipe, "plot 'Messung2.log' with linespoints pointtype 7 lc rgb 'red' \n");															//Logdatei mit Optionen plotten
		fflush(gnupipe);																																//gesamten Datenstrom an Gnuplot übertragen
		_pclose(gnupipe);																																//Pipe zu Gnuplot schließen

	//************************Keystroke abwarten**********************************//
#ifdef _WIN32
		std::cout << "Plot wurde erstellt.\nZum Beenden <ENTER> druecken." << std::endl;																//Keystroke abfragen, damit Gnuplot unter Windows geöffnet bleibt
		std::cin.get();
#endif
	
	}

	return 0;
}