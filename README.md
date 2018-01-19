CellularAutomaton Version 12.03a 16/01/2018

Autorenschaft: 	Nicolai Gennrich, Sahra Teichmann, 
				Marian Stiehler, Carina Pfaff

				
Benutzungshinweise
-------------------------------------------------------------------------
- getestet unter Windows, Mac und Linux


Beschreibung des Projektes
-------------------------------------------------------------------------
- Implementierung des Spiels Predator-Prey
- Implementierung des Spiels Snake (Siehe README_SNAKE.md)
- Implementierung des Spiels Convey's Game of Life (Siehe README_GOL.md)


Struktur des Programms
-------------------------------------------------------------------------
- CAbase dient als GUI des zellulären Automaten für die Spiele GameofLife, Snake und PredatorPrey
- im Konstruktor werden die Spieleobjekte erzeugt.
- über verschiedene Modi wird auf die unterschiedlichen Spiele verwiesen (updateSelectedGame)
- mit Hilfe eines Timers wird das Spielfeld im Interval aktualisiert

jetzt: Spielmodus PredatorPrey
- Konstruktor setzt Basiswerte.
- moveCells(): bewegt jede Zelle auf ein moegliches neue Feld.
- possibleCellMoves(): gibt die Position von Futter und freien Zellen in einer Liste zurueck.
- cellIsDying(): entfernt eine Zelle, wenn ihre Lebenszeit 0 erreicht.
- clear: leer das Feld.
- newGame: erstellt ein neues Spiel, Zellen werden random gesetzt.
- finish: Prueft auf Gewinn
- uncheckCells: Da Zellen sich inplace bewegen, werden nach dem beenden eines Bewegungszykluses, alle
		Zellen auf nicht gecheckt gesetzt.

Bedienung GUI
-------------------------------------------------------------------------
- Der Spielmodus wird über die ComboBox ausgewählt (GameofLife, Snake, PredatorPrey)
- Durch den Startbutton wird das Spiel gestartet
- Durch Betätigung des Pausebuttons pausiert das Spiel (Wiederaufnahme mit "start")
- der "clear"-Button leert das Feld
- der "new game" Button, erstellt ein neues Spiel
- Zellengröße wird durch das Universe-Size Feld gesteuert (quadratisches Spielfeld) (10 - 100 Zellen)
- Steuerung der Geschwindigkeit des Spielablaufes über das Generation Interval (100 - 100000ms)
- Zellen koennen durch klicken des Spielfelds neu gesetzt werden.(Zellmode abhaengig vom CellMode)
- Veraenderung der Lebenszeit wird erst nach beginn eines neuen Spiels fuer alle Zellen gesetzt.


Feedback zu Milestone3
-------------------------------------------------------------------------
- Unverstaendliche Aufgabenstellung
- Aufgabenstellung verlangt zu wenig Programmierung im OOP-Stil