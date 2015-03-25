# pipe
Beispiel 2

Schreiben Sie eine kleine Library mit den zwei Funktionen mypopen() und mypclose(), die sich wie popen(3) bzw. pclose(3) verhalten (siehe Skriptum oder Online-Manual). Implementieren Sie diese beiden Funktionen in einer eigenen Übersetzungseinheit namens mypopen.c und exportieren Sie alle nötigen Informationen (z.B., die extern Deklarationen) in einem zugehörigen Headerfile namens mypopen.h.

Mit Hilfe der Funktionen mypopen() und mypclose() können Sie relativ einfach ein Shell-Kommando ausführen und das Ergebnis direkt in ein Programm einlesen und weiterverarbeiten bzw. Daten, aus einem Programm heraus, an dieses Kommando übergeben.

popen(command, "r") liefert einen Filepointer auf eine pipe, von der die Ausgabe des Befehls command gelesen werden kann. popen(command, "w") liefert einen Filepointer auf eine pipe, auf die die Eingabe für den Befehl command geschrieben werden kann.

- main muss nicht programmiert werden, befindet sich am Server

Anleitung:
mypopen() muß zunächst eine Pipe einrichten (pipe(2)) und dann einen Kindprozeß generieren (fork(2)). Im Kindprozeß ist das richtige Ende der Pipe ("r" oder "w") mit stdin bzw. stdout zu assoziieren (dup2(2)) und das im 1. Argument spezifizierte Kommando auszuführen (execl(3) oder execv(3)). Verwenden Sie - wie die Funktion popen(3) - zum Ausführen des Kommandos die Shell sh(1). Als letztes muß mypopen() von einem Filedeskriptor einen passenden FILE * mit fdopen(3) erzeugen.

Bei Aufruf von mypclose() soll der aufrufende Prozeß auf die Terminierung des Kindprozesses warten (waitpid(2)). Zur Vereinfachung soll immer nur höchstens eine Pipe mit mypopen() geöffnet werden können. Stellen Sie dies in ihrer Implementierung sicher.

Signalbehandlung ist für dieses Beispiel nicht notwendig.

Fehlerbehandlung:
mypopen() soll sich (analog zu popen(3)) wie eine Libraryfunktion verhalten. D.h. es wird niemals irgendwas auf stderr (oder sonst wohin) geschrieben - die Entscheidung, ob das Nicht-funktionieren (bzw. auch das Funktionieren) der Libraryfunktion einen Fehler für die Applikation darstellt, obliegt immer der Applikation. Selbiges gilt auch für Fehlermeldungen bzw. die Art und Weise derselben.

Jeglicher schief gegangene System-Call sowie sonstige Fehler sind über den Returnwert der Funktion "nach oben" zu melden. Im Falle von mypopen() ist auch errno passend zu erhalten (falls ein System-Call einen Fehler meldet) bzw. direkt zu setzen (z.B. falls unerwartete/falsche Parameter übergeben werden ist EINVAL ein guter Wert dafür).

Weiters fork(2)t die Libraryfunktion auch, und auch im Kindprozeß können Fehler auftreten (z.B. könnte execv(3) schief gehen). Im Kindprozeß darf nie ein return passieren, weil dann die mypopen() Funktion 2 Mal zurückkommt - einmal im Elternprozeß und einmal im Kindprozeß - und damit rechnet keine Applikation.

