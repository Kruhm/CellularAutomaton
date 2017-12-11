Titel: GameOfLife Version 1.0 22/11/2017

Autorenschaft: 	Sahra Teichmann (6319245), Nicolai Gennrich (6375425),
				Marian Stiehler (6074535), Carina Pfaff (5852091)

			
Benutzungshinweise
-----------------------------------
- getestet unter Windows, Mac und Linux


Beschreibung des Projekts
-----------------------------------
- Einführung in die Programmiersprache C++ über vorwiegend Aufgabe 1
- Implementierung Conways Game Of Life (Spielregeln unter https://de.wikipedia.org/wiki/Conways_Spiel_des_Lebens)
	- Aufgabe 2) Konsolenbasiert
	- Aufgabe 3) mithilfe GUI-Toolkit Qt
	
	
Struktur des Programms
-----------------------------------
Aufgabe 2)
- Konstruktor erzeugt ein 30x30 Feld (zellulärer Automat, mit Hilfe dyn. Arrays) [setSize, setX, setY]
- Zellen des Feldes auf False (= tot) gesetzt [wipe, setCellState, setNewCellState]
- Ausgabe des Menüs (über while-Schleife erzeugt) zeigt an, welche Möglichkeiten der User hat [menu]:
	- Exit: Bedingung der while-Schleife des Menüs wird nicht mehr erfüllt; Programmende
	- Evolve: Evolutionsschritt [evolve]
				jede Zelle bekommt ihren (ggf. neuen) Status im nachfolgenden Evolutionsschritt, indem jede Zelle auf die Regeln des Spiels überprüft wird [setNewCellState, apply_rules]
				es wird der neue Status dem aktuellen Übergeben, danach wird der neue Zustand standardmäßig auf False gesetzt [setCellState, getNewCellState, setNewCellState]
	- Change cell: Status der Zelle wird vom Benutzer geändert, durch Eingabe der jeweiligen Koordinaten und des gewünschten Zellenstatus [setCellState]
	- Reprint: Feldausgabe, mit aktuellem Zellenstatus [show, getCellState]
	- Resize: Änderung Größe des Feldes; durch Eingabe der jeweiligen Koordinaten [setSize]
	
Aufgabe 3)
- Funktionsweise in Aufgabe 3) ähnlich zu der in Aufgabe 2); Unterschiede durch die Benutzung eines GUI werden im Folgenden erläutert
- Erstellung der Applikation und des Windows
- Verwendung eines Timers als eine Art Steuerelement, Verbindung mit im QtCreator erstellten UI
- Größe des Feldes über den Wert im (universeSize)-Feld bestimmt
- Gittererstellung [setSize]
- beispielhafter "Gleiter" wird erstellt
- durch den Timer werden die Spielzyklen gesteuert (Verbindung Timer mit [evolve]), Zyklendauer wird der intervalBox entnommen
- Betätigung des Stop-Buttons stoppt den Timer [on_stopButton_clicked]
- Betätigung des Start-Buttons startet den Timer wieder [on_startButton_clicked]
- change!-Button für die Größenveränderung des Universums zuständig, durch uptdate mit neuen Werten aus der universeSize-Box [on_changeUniverseSizeButton_clicked]
- Clear-Button für Aufruf von [on_clearButton_clicked] zuständig, welche wiederum [wipe] initialisiert (timer wird danach gestoppt & update)
- die Änderung des Zeitintervalls wird durch [on_intervalBox_valueChanged] (wartet auf eine Änderung) durchgeführt, dazu wird der timer gestoppt und anschließend mit dem neuen Intervallwert (mit dem der timer läuft) gestartet
- [paintEvent] ist dafür zuständig, dass Spielfeld "gezeichnet" wird
- [mousePressEvent] ändert durch Mausklicks den Zellstatus (False -> True, bzw. tot -> lebendig und andersherum)


Bedienung GUI
-----------------------------------
- Spiel startet mit einem voreingestelltem Muster (Gleiter) als Beispiel

- Stop-Button: stoppt das Evolutionsspiel und hält im aktuellen Zustand an
- Start-Button: startet das Evolutionsspiel ausgehend vom aktuellen Zustand der Zellen
- Clear-Button: setzt alle Zellen in den Zustand "tot"

- Universe Size: verändert die Spielfeldgröße zu einem quadratischen Feld mit Länge und Breite der Eingabe
	-> Ausführung durch <change!>
- Generation Interval: legt fest, in welchen zeitlichen Abständen ein Evolutionsschritt ausgeführt werden soll (in ms)
	-> Änderung der zeitlichen Angabe führt zur direkten zeitlichen Änderung
- Statusänderung der Zellen(von lebendig nach tot oder tot nach lebendig) über Mausklick auf die entsprechende Zelle
	Feature: auch über die Eingabefelder <x>, <y> können die Zellen ihren Stautus ändern
		-> Ausführung durch <change cell>
	
- Save: todo
- Load: todo

	
Probleme
------------------------------------
- Fehler zu Beginn in der Aufgabenstellung (dieser wurde nachträglich durch die Praktikumsleitung behoben)
- Kits in Qt
- Arbeit mit Qt


Feedback zu Milestone1
-----------------------------------

- da es sich um eine heterogen (programmier-)erfahrene Gruppe handelt liegt der empfundene Schwierigkeitsgrad von passend bis überfordernd
- zu große Diskrepanz zwischen in der Vorlesung vermitteltem Wissen und Aufgabenstellung
- Aufgabe 1 war gut um sich mit C++ das erste Mal auseinander zu setzen. Der Unterschied des Schwierigkeitsgrades zwischen Aufgabe 1 und 3 ist jedoch enorm
- leider wurde von den Aufgabenstellern auf die Verwendung veralteter/ nicht empfohlener Methoden hingewiesen (dyn. Array statt Vektor)


