# Streaming

### 1. Wozu dient der Jitter-Puffer in einem Streaming-Empfänger?
*Quelle: Streaming-Verfahren, Folie 20*

- Fängt Pakete auf und speichert sie zwischen, Ziel: Eliminierung der Schwankung
Der Jitter-Puffer kompensiert Schwankungen in der Netzverzögerung bei der Übertragung von Streaming-Daten.

### 2. Wie erhält man die optimale Verzögerung des Puffers?
*Antwort nicht direkt in Folien zu finden*

- abhängig von Anwendung

Die optimale Pufferverzögerung wird durch Abwägung zwischen:
- Minimaler Latenz 
- Ausgleich von Netzwerk-Jitter
- Verfügbarer Bandbreite
bestimmt.

### 3. Was sind die Vorteile des MPEG-DASH-Verfahrens zum HTTP-Pseudostreaming?
*Quelle: Streaming-Verfahren, Folie 13*

MPEG-DASH bietet:
- Unterstützung von Live-Video
- Adaptive Qualitätsanpassung während der Übertragung  
- Standardisiertes Format (ISO/IEC 23009-1:2012)

### 4. Welche Browserunterstützung ist für MPEG-DASH notwendig?
*Quelle: Streaming-Verfahren, Folie 13*

Browser benötigen:
- Media Source Extensions (MSE)
- Fähigkeit, Bytestreams via JavaScript an Codecs zu senden
- Chrome unterstützt dies nativ

### 5. Was ist der wesentliche Vorteil eines auf UDP-basierenden Streaming-Protokolls?
*Quelle: Streaming-Verfahren, Folie 21*

UDP ermöglicht:
- Konstante Senderate ohne Rücksicht auf Netzwerküberlastung
- Kleinere Puffer für Jitter-Ausgleich im Vergleich zu TCP
- Keine verzögerte Auslieferung durch Übertragungswiederholungen
- interaktive Nutzung

### Protokolle zur Medienübertragung bei BBB

- WebRTC -> Web Real Time Communication
- SIP -> Session Initiation Protocoll

### Berechnen Sie anhand der Vorgaben aus Bandwidth Requirements die Eingangs- Ausgangsdatenraten am Server und an den Clients bei einer Konferenz mit 30 Teilnehmern und folgenden Szenarien (Videoauflösung 320x240, Audio nur beim Präsentator). Was können Sie aus den Ergebnissen ableiten? 
1. Video bei allen an 
2. Video nur beim Präsentator an

- geg.: 
    Y = 0.25 Mbit/s
    A = 0.04 Mbit/s
    U = 30 (Users)
    W = 30 (Webcams)

- Lösung:
1.  W = 30
    Server in:      W * Y = 7.5 Mbit/s
    Server out:     W * (U-1) * Y = 217.5 Mbit/s
    Client in:      (U-1) * Y + A = 7.29 Mbit/s (downstream)
    Client out:     Y + A = 0.29 Mbit/s (upstream)

2.  W = 1
    Server in:      W * Y = 0.25 Mbit/s
    Server out:     W * (U-1) * Y = 7.25 Mbit/s
    Client in:      Y + A = 0.3 Mbit/s
    Client out:     Y + A = 0.3 Mbit/s



# RTSP (Real Time Streaming Protocol)

### 1. Wozu dient das RTSP konkret und was ist der Unterschied zum RTP?
*Quelle: RTSP-Folien, Folie 3*

RTSP:
- Anwendungsprotokoll zur Steuerung von Medienströmen
- Entspricht einer "Netzwerk-Fernbedienung"
- Steuert nur den Stream, überträgt keine Mediendaten
- Out-of-Band-Steuerung (Port 554)

Unterschied:
- mit RTSP werden Parameter ausgehandelt, über RTP erfolgt Datenübertragung

### 2. Auf welcher OSI-Schicht ist der Standard angesiedelt?
*Quelle: RTSP-Folien, Folie 3*

Anwendungsschicht (Layer 7), da es ein Anwendungsprotokoll ist

### 3. Was sind die Unterschiede zu HTTP?
*Quelle: RTSP-Folien, Folie 3, 10*

- RTSP ist zustandsbehaftet (HTTP zustandslos)
- RTSP verwendet eigene Session- und Sequenznummern
- Spezielle Kommandos für Mediensteuerung (PLAY, PAUSE etc.)
- Out-of-Band Kontrolle der Mediendaten

### 4. Welche Zustände besitzt RTSP?
*Quelle: RTSP-Folien, Folie 10*

- INIT (Initialzustand)
- READY (nach SETUP)
- PLAYING (nach PLAY)
- Wechsel durch SETUP, PLAY, PAUSE, TEARDOWN

### 5. Welche Methoden ändern den Zustand eines RTSP-Server?
*Quelle: RTSP-Folien, Folie 8*

- SETUP (INIT -> READY)
- PLAY (READY -> PLAYING)
- PAUSE (PLAYING -> READY)
- TEARDOWN (-> INIT)

### 6. Welche Methoden muss ein RTSP-Server mindestens unterstützen?
*Quelle: RTSP-Folien, Folie 13*

Minimaler Server muss unterstützen:
- SETUP
- TEARDOWN
- OPTIONS
- PLAY oder RECORD (je nach Servertyp)

### 7. Wie ist der Aufbau eines allgemeinen Requests?
*Quelle: RTSP-Folien, Folie 11*

- Request-Zeile 
- Header-Felder
- Leerzeile
- Optional: Body

- <METHODE> <URI> RTSP/<VERSION>

### 8. Wie ist der Aufbau der Request-Zeile?
*Quelle: RTSP-Folien, Folie 11*

`Method URI RTSP/1.0`

### 9. Wie ist der Aufbau der Request-URI?
*Quelle: RTSP-Folien, Beispiele auf Folie 12, 15*

Format: `rtsp://server[:port]/path`

### 10. Welche Zeichen werden als Zeilentrennzeichen verwendet?
*Quelle: Beispiele in RTSP-Folien*

CRLF (Carriage Return Line Feed)

### 11. Welcher Zeichensatz mit welcher Codierung wird für RTSP verwendet?
*Antwort nicht direkt in Folien zu finden*

UTF-8 Kodierung

### 12. Wie ist der Aufbau eines allgemeinen Response?
*Quelle: RTSP-Folien, Folie 11*

- Status-Zeile (Version Status-Code Reason-Phrase)
- Header-Felder
- Leerzeile
- Optional: Body

- <STATUS>;
- <GENERAl HEADER> | <RESPONSE HEADER>
- <Leerzeile>
- <Payload>

### 13. Wofür dient das Attribut CSeq?
*Quelle: RTSP-Folien, Folie 10*

- Sequenznummer für Zuordnung von Request und Response
- Wird vom Client bei jeder Nachricht erhöht
- Server wiederholt die Nummer in der Antwort

### 14. Wie lautet ein minimaler OPTION- bzw. DESCRIBE-Request?
*Quelle: RTSP-Folien, Folie 18*

OPTION: OPTIONS * RTSP/1.0
        CSeq: 1

DESCRIBE: rtsp://server/media.mp4 RTSP/1.0

### 15. Skizzieren Sie einen typischen Setup-Request + Response
*Quelle: RTSP-Folien, Folie 15*

Request:
SETUP rtsp://example.com/media RTSP/1.0
CSeq: 302
Transport: RTP/AVP;unicast;client_port=4588-4589

Response:
RTSP/1.0 200 OK
CSeq: 302
Session: 47112344
Transport: RTP/AVP;unicast;client_port=4588-4589;server_port=6256-6257

### 16. Skizzieren Sie kurz den Ablauf einer minimalen RTSP-Session bezüglich des Abspielens eines Videostreams
*Quelle: RTSP-Folien, Folie 9*

1. Client sendet SETUP für Stream-Initialisierung
2. Server antwortet mit Session-ID
3. Client sendet PLAY
4. Medienübertragung startet
5. Optional: PAUSE/PLAY
6. TEARDOWN zum Beenden

### 17. Wozu dient das SDP im Kontext von RTSP?
*Quelle: RTSP-Folien, Folie 19*

SDP (Session Description Protocol):
- Beschreibung der Eigenschaften von Multimediadatenströmen
- Vermittelt Format, Codecs, Timing
- Wird in DESCRIBE Response übertragen

### 18. Schauen Sie sich Beispiele zu SDP aus [RFC 2327], [RFC 4317] an.
*Quelle: RTSP-Folien, Folie 20*

Beispiel-SDP enthält:
- Versionsangabe (v=)
- Sitzungsbeschreibung (s=)
- Zeitinformationen (t=)
- Medientypen (m=)
- Attribute (a=)

### 19. Was bedeuten in RTSP die Begriffe: Message, Request, Response, Presentation, Session
- Message: Befehl zum Verbindungsaufbau.
- Request: Eine RTSP-Anfrage. (Wenn eine HTTP-Anfrage gemeint ist, wird dies explizit angegeben.)
- Response: Eine RTSP-Antwort.
- Presentation: Ein Satz von einem oder mehreren Streams, die dem Client als vollständiger Medienfeed unter Verwendung einer Präsentation Beschreibung wie unten definiert präsentiert werden.
- Session: Eine live Presentation. Eine vollständige RTSP- "Transaktion", z. B. das Betrachten eines Films.

### 20. Wie lautet eine mögliche Serverantwort? 
- RTSP 200 OK

### 21. Wie lautet der Statuscode für OK? 
- 200

### 22. Wofür dient die SETUP-Methode und wie lautet ein vollständiger SETUP-Request und SETUP-Response? 
- SETUP rtsp://<uri> RTSP/1.0
- CSeq: <Nr.>
- Transport: RTP/AVP; unicast; clinet_port



# RTP (Real Time Protocol)

### 1. Was ist die generelle Aufgabe von RTP und wie ist die Verhältnis zu RTSP?
*Quelle: RTP-Folien, Folie 4*

RTP:
- Übertragung von echtzeitnahen Multimedia-Datenströmen über IP
- Arbeitet auf UDP (Unicast/Multicast)
- RTSP steuert nur den Stream, RTP überträgt die eigentlichen Mediendaten

### 2. Welche Felder umfasst ein minimaler RTP-Header?
*Quelle: RTP-Folien, Folie 6*

- Version (V): 2 Bit
- Padding (P): 1 Bit 
- Marker (M): Anwendungsspezifisch
- Payload Type (PT): Codec-Identifikation
- Sequenznummer: 16 Bit
- Timestamp: 32 Bit
- SSRC: 32 Bit Synchronisationsquelle

### 3. Was ist ein Translator und was ein Mixer im RTP-Umfeld?
*Quelle: RTP-Folien, Folie 5*

Translator:
- Weiterleitung und mögliche Umkodierung von Paketen
- SSRC bleibt unverändert

Mixer: 
- Kombiniert mehrere Quellen
- Generiert eigene Timing-Informationen
- Bekommt eigene SSRC-ID

### 4. Warum ist es sinnvoll, die maximale Größe eines RTP-Paketes auf die MTU zu begrenzen?
*Quelle: RTP-Folien, Folie 24*

- Vermeidung von IP-Fragmentierung
- Bessere Übertragungseffizienz
- Geringere Paketverlustwahrscheinlichkeit

### 5. Wozu dient RTCP?
*Quelle: RTP-Folien, Folie 8*

RTCP (RTP Control Protocol):
- Kontrollkanal für Statusnachrichten
- QoS-Monitoring und Feedback
- Teilnehmeridentifikation
- Aushandlung von Dienstgüteparametern

### 6. Welche Möglichkeiten existieren, um Mediendaten zu verschlüsseln?
*Quelle: RTP-Folien, Folie 16-17*

- SRTP (Secure RTP)
- ZRTP für Schlüsselaustausch
- Verschlüsselung des Payloads
- Authentifizierung von Header + Daten

### 7. Ermitteln Sie die Payload-Typen (PT) für JPEG-video und MPEG Layer 3 - Audio.
*Quelle: RTP-Folien, Folie 7*

- JPEG Video: PT 26
- MPEG Audio: PT dynamisch (96-127)

### 8. Warum ist ein dediziertes Format für JPEG-over-RTP sinnvoll?
*Quelle: RTP-Folien, Folie 24-25*

- Bilder oft größer als MTU/max UDP
- Ermöglicht RTP-Fragmentierung statt IP-Fragmentierung
- Spezielle Header für JPEG-Parameter
- Restart-Marker für Fehlerbehandlung

### 9. Wozu dient der JPEG-Restart-Marker?
*Quelle: RTP-Folien, Folie 23*

- Ermöglicht Wiederaufnahme der Dekodierung nach Übertragungsfehlern
- Definiert Synchronisationspunkte im Datenstrom

### 10. Ermitteln Sie die konkrete Erhöhung des TimeStamps für ein 20ms Audio-Paket bei 8kHz Abtastung und für Video (90kHz) für folgende Bildwiederholraten: 24, 25, 30, 50 und 60 Hz. Was fällt Ihnen auf?
*Antwort nicht direkt in Folien zu finden*

Audio (8kHz, 20ms):
- Erhöhung = 8000Hz * 0.02s = 160 Samples

Video (90kHz):
- Rechnung: 90000Hz / gegebene Hz

- 24 Hz: 3750 Samples
- 25 Hz: 3600 Samples
- 30 Hz: 3000 Samples
- 50 Hz: 1800 Samples
- 60 Hz: 1500 Samples

Auffällig: Lineare Abnahme der Samples pro Frame bei steigender Framerate



# Kanalmodelle und Verfahren

### 1. Wie unterschieden sich die Kanalmodelle BSC und BEC?
**Quelle:** FEC-Einführung, Folie 3
- BSC (Binärer Symmetrischer Kanal): Bits können mit Wahrscheinlichkeit Pb verfälscht werden (0→1 oder 1→0)  
- BEC (Binärer Auslöschungskanal): Bits werden mit Wahrscheinlichkeit Pb gelöscht/unkenntlich (→E)

**Quelle:** Blockcodierung, Folie 4, 5
- BSC: Diskrete Bitfehler mit Wahrscheinlichkeit P
- AWGN: Kontinuierliches additives weißes Gaußsches Rauschen, das dem Signal überlagert wird
- Durch Quantisierung kann AWGN in BSC überführt werden

- BSC-> Symmetrisch d.h. 0 bit werden genau so behandelt wie 1 bits - Wird meist für eine erste Näherung verwendet und ist gut für den physical layer geeignet
- BEC-> Entweder das bit kommt an oder nicht durch eventuell Auslöschung. Gilt für 0 und 1 bits. Daraus folgt es gibt den 0,1 und Auslöschungszustand

### 2. Welcher Kanal hat bei 50% Fehlern eine höhere Kanalkapazität?
**Quelle:** FEC-Einführung, Folie 6
Der BEC hat bei 50% Fehlern eine höhere Kanalkapazität:
- BEC: C = 1 - Pe = 0.5
- BSC: C = 1 + Pe·log2(Pe) + (1-Pe)·log2(1-Pe) ≈ 0

### 3. Welcher Kanal ist besser für die Modellierung der Übertragung auf Anwendungsebene geeignet und warum?
**Quelle:** FEC-Einführung, Folie 3
- Der BEC ist besser geeignet, da er die IP-Übertragung (best effort) modelliert, bei der Pakete entweder korrekt ankommen oder verloren gehen. Der BSC modelliert eher die physikalische Schicht.

### 4. Warum ist des u.U. sinnvoll, den Fehlerschutz zusätzlich zur Bitübertragungsebene auch auf Anwendungsebene anzuwenden?
**Quelle:** Implizit aus FEC-RFCs
- Weil Paketverluste auf Anwendungsebene andere Charakteristiken haben als Bitfehler auf der physikalischen Ebene. Ein Ende-zu-Ende Fehlerschutz kann Verluste auf allen Netzwerkebenen abdecken.
- Es wird versucht,den Fehlerschutz an bestimmten Schichten zu deaktivieren --> geringere Overhead
- Beispiel: UDPlite

### 5. Welche Vorteile hat das FEC-Verfahren mittels Parity Check im Gegensatz zur Verdopplung des Datenstroms?
**Quelle:** FEC-Einführung, Folien 8-9
- Geringerer Overhead (50% vs. 100%)
- Kann bei geschickter Wahl der FEC-Pakete auch mehrere aufeinanderfolgende Paketverluste korrigieren
- Es kann mindestens ein Paket innerhalb von k+1 Paketen kann rekonstruiert werden 

### 6. Wozu dient Interleaving im Kontext einer Datenübertragung?
**Quelle:** FEC-Einführung, Folie 16
Interleaving verteilt angrenzende Daten über einen größeren Bereich, um gehäufte Blockverluste (Bursts) in verteilte Einzelverluste umzuwandeln. Dies ist besonders wichtig für Multimediadaten.

### 7. Wann ist Interleaving nicht sinnvoll?
**Quelle:** FEC-Einführung, Folie 16, 19
Interleaving ist nicht sinnvoll bei Echtzeitdiensten, da es zusätzliche Verzögerung (Latenz) verursacht.

### 8. Wozu dient Unequal Error Protection?
**Quelle:** FEC-Einführung, Folie 20
UEP schützt wichtige Daten stärker als unwichtige, besonders relevant bei quellencodierten Multimediadaten. Beispiel: Im Skype-Codec SILK werden wichtige Daten im Folgepaket wiederholt.

### 9. Was ist das Ziel der Fehlerverdeckung?
**Quelle:** FEC-Einführung, Folie 21
Fehlerverdeckung (Error Concealment) wird angewendet, wenn trotz FEC Paketverluste auftreten. Ziel ist es, fehlende Daten durch Interpolation oder Wiederholung zu ersetzen. Funktioniert nur gut bei kurzen Lücken.

### 10. Bestimmen Sie die Restfehlerwahrscheinlichkeit bei einer Paketverlustwahrscheinlichkeit von 1% und einem Schutz von jeweils zwei Medienpaketen mit einem Paritätspaket!
**Quelle:** FEC-Einführung, Folie 11

Gruppengröße: k = 2
Blockfehlerwahrscheinlichkeit:  p = 0.01

Ansatz Paul:
Pok = (1-p) ^ 3 + 3p (1-p) ^ 2 = 0.9703 + 0.0294 = 0.99967%
Pr  = 1 - Pok = 0.03%

Ansatz Theo:
Pr = 1 - [(1-P)^3 + 3P(1-P)^2]
= 1 - [(0.99^3 + 30.010.99^2)]
= 1 - [0.970299 + 0.029403]
= 0.000298 ≈ 3E-4

### 11. Berechnen Sie die Blockfehlerwahrscheinlichkeit bei einer Übertragung über einen Binär-Kanal mit einer Bitfehlerwahrscheinlichkeit (BER) von Pb = 10^-2
**Quelle:** Blockcodierung, Folie 14
Die Wortfehlerwahrscheinlichkeit nach der Decodierung beträgt:
Pw ≤ Σ(n,d=t+1) (n,d) P^d_e · (1-Pe)^(n-d)

### 12. Warum sollte eine Fehlerkennung auf den Schichten 1/2 für RTP-Daten u.U. deaktiviert werden?
- Die erhöhte Latenz bei  Fehlererkennung z.B. durch von Interleaving ist hinderlich für Echtzeit nahe Anwendungen

### 13. Wie unterscheidet sich der AWGN-Kanal vom BSC-Kanal?
AWGN:
- Kontinuierlich
- Eingangs- und Ausgangswerte sind beliebige reelle Werte
- additives, weißes Rauschen

BSC:
- Diskret
- Eingangs- und Ausgangswerte sind binäre Werte
- binäre Fehlerwahrscheinlichkeit

### Bestimmen Sie die Kanalkapazität des AWGN-Kanals bei einem SNR von 20 dB!
- Ergebnis: 6.65 Bit/s/Hz



# RFC für FEC

### 1. **Warum ist es sinnvoll, eine FEC-Nutzung auf Anwendungsebene (OSI-Modell) zu standardisieren?**
- **Antwort:**  Die Standardisierung auf Anwendungsebene ermöglicht eine flexible und dynamische Anpassung der FEC-Parameter an die spezifischen Anforderungen der Medien- und Kanalcharakteristiken. 
                Dies ist besonders wichtig für Multimedia-Anwendungen wie Audio und Video, bei denen die Netzwerkbedingungen variieren können. 
                Zudem ist die Implementierung auf Anwendungsebene unabhängig von der darunterliegenden Netzwerkinfrastruktur, was die Kompatibilität mit verschiedenen Systemen und Protokollen gewährleistet.
- **Quelle:** `it2-25-fec-rfc_print.pdf`, Folie 5.

### 2. **Welche Vorteile bietet RFC 5109 im Gegensatz zu einer simplen statischen Nutzung von FEC?**
- **Antwort:**  RFC 5109 bietet die Möglichkeit, die FEC-Parameter dynamisch anzupassen, was eine bessere Anpassung an die aktuellen Netzwerkbedingungen ermöglicht. 
                Es unterstützt verschiedene Schutzlängen und -stufen sowie unterschiedliche Gruppengrößen. 
                Zudem ist es vollständig kompatibel mit Empfängern, die keine FEC-Unterstützung haben, da die Medienpakete unverändert gesendet werden können.
- **Quelle:** `it2-25-fec-rfc_print.pdf`, Folie 4 und 5.

### 3. **Auf welchem FEC-Verfahren basiert RFC 5109?**
- **Antwort:** RFC 5109 basiert auf dem **XOR-Verfahren** (Exklusiv-Oder), das zur Erzeugung von FEC-Paketen verwendet wird. Dieses Verfahren ist einfach zu implementieren und effizient in der Fehlerkorrektur.
- **Quelle:** `it2-25-fec-rfc_print.pdf`, Folie 4.

### 4. **Für welche Anwendungen ist die Uneven Level Protection (ULP) sinnvoll?**
- **Antwort:**  Die Uneven Level Protection (ULP) ist besonders sinnvoll für **Audio- und Videoanwendungen**, bei denen bestimmte Teile der Daten wichtiger sind als andere. 
                Durch ULP können kritische Daten besser geschützt werden, während weniger wichtige Daten mit geringerer Redundanz übertragen werden.
- **Quelle:** `it2-25-fec-rfc_print.pdf`, Folie 7.

### 5. **Welche Gruppengrößen sind mit RFC 5109 möglich?**
- **Antwort:**  RFC 5109 ermöglicht die Verwendung von **variablen Gruppengrößen**, die an die spezifischen Anforderungen der Anwendung angepasst werden können. 
                Es gibt keine feste Begrenzung, aber die Gruppengröße wird typischerweise durch die Anzahl der zu schützenden Medienpakete und die gewünschte Redundanz bestimmt.
- **Quelle:** `it2-25-fec-rfc_print.pdf`, Folie 4 und 5.

### 6. **Wie kann der Beginn des nächsten Level-Headers ermittelt werden?**
- **Antwort:**  Der Beginn des nächsten Level-Headers kann durch die **Länge des aktuellen Level-Payloads** ermittelt werden. 
                Die Länge des Payloads wird im FEC-Level-Header angegeben, sodass der nächste Header direkt im Anschluss beginnt.
- **Quelle:** `it2-25-fec-rfc_print.pdf`, Folie 11.

### 7. **Was bedeutet SN-Base?**
- **Antwort:**  **SN-Base** steht für die **Sequenznummer des ersten Medienpakets** in der Gruppe, die durch das FEC-Paket geschützt wird. 
                Es ist die niedrigste Sequenznummer aller Medienpakete, die in der FEC-Gruppe enthalten sind.
- **Quelle:** `it2-25-fec-rfc_print.pdf`, Folie 10.



# Übungsaufgaben Grundlagen FEC
## 1. Vergleich FEC/ARQ-Protokoll

### 1.1 Bestimmen Sie die theoretisch minimale Verzögerung eines optimalen ARQ-Protokolls bei Auftritt eines Paketverlustes
**Quelle:** FEC-Einführung, Aufgabenblatt S.1
- Ende-zu-Ende-Verzögerung: TE-E = 140 ms
- Übertragungsverzögerungen und Verarbeitungsverzögerungen werden vernachlässigt

**Antwort ChatGPT und Discord**
- Minimale Verzögerung: 3 * TE-E = 420 ms (Hinweg für das verlorene Paket, Rückweg, Hingwe für neues Paket)

**Antwort Theo**
- Minimale Verzögerung: 2 * TE-E = 280 ms (für Erkennung des Verlusts und erneute Übertragung)

#### 1.2 Nennen Sie Vorteile/Nachteile eines reinem FEC-Übertragungsverfahrens gegenüber einem ARQ-Verfahren.
Vorteile:
- Latzenen sind geringer selbst mit Fehler
- Erhöhte Kanallast bei keine Fehler
- kein Rückkanal z.B. bei Multicast

Nachteile:
- höherer Aufwand durch Codieren/Decodieren


## 2. FEC-Verfahren mittels Party-Check-Code
Es ist eine Echtzeitübertragung mittels RTP-Protokoll geplant. Die Anwendung arbeitet mit 100 Paketen/s und 1000 Bit pro Paket. 
Die Paketverlustwahrscheinlichkeit wurde durch statistische Analyse über einen längeren Zeitraum mit 1% ermittelt und es wird von unabhängigen Paketverlusten auf der Übertragungsstrecke ausgegangen.

### 2.1 Geben Sie die Kanalkapazität der Verbindung an!
**Quelle:** FEC-Einführung, Aufgabenblatt S.1
- Daten: 100 Pakete/s, 1000 Bit pro Paket
- Kanalkapazität ist die theoretisch über einen gestörten Kanal maximal fehlerfrei übertragbare Datenrate. (FEC-Einführung S. 6)

**Antwort Discord**
- Kanalkapazität (C) = (1-p) * Bitrate = 0.99 * 100 kbit/s = 99 kbit/s = 99 Pakete/s

**Antwort Theo**
- Kanalkapazität = 100 * 1000 = 100.000 Bit/s = 100 kBit/s

### 2.2 Welche Verfahren zur Vermeidung von Paketverlusten schlagen Sie vor, wenn Sie den Verlust von maximal einem Paket innerhalb in 5 übertragenen Paketen verhindern wollen? Wie groß ist der jeweilige Overhead bzw. die Coderate? 
- XOR-FEC mit k=4, p=1, n=k+p
- Overhead: p/k=25%
- Coderate: R=k/n=0.8

### 2.3 Berechnen Sie die Wahrscheinlichkeit für einen Paketverlust auf Anwendungsebene trotz der im obigen Aufgabenpunkt eingesetzten Codierung (Restfehler). 
Pr = 1 - ((1-p)^(k+1) + [k+1,1]*p*(1-p)^k)
Pr(k=4) = 0.001

### 2.4 In welchen zeitlichen Abständen ist jeweils im Mittel mit einem Restfehler zu rechnen? 
- 100 Pakete/s -> statistisch 1 Paketverlust pro Sekunde -> Restfehler im Mittel alle 10s


## 3. Fehlererkennung und Fehlerkorrektur
Es ist ein Kanalcode mit (n,k,dmin) = (31,15,5) gegeben.

### 3.1 Wieviele Fehler kann dieser Code erkennen?
**Quelle:** FEC-Einführung, Aufgabenblatt S.1
- Anzahl erkennbarer Fehler = dmin - 1 = 4 Fehler
- Code kann 4 Fehler erkennen

### 3.2 Wieviele Fehler kann dieser Code korrigieren?
**Quelle:** FEC-Einführung, Aufgabenblatt S.1
- Anzahl korrigierbarer Fehler = ⌊(dmin-1)/2⌋ = ⌊4/2⌋ = 2 Fehler
- Code kann 2 Fehler korrigieren

### 3.3 Wieviele Ausfallstellen kann dieser Code korrigieren?
**Quelle:** FEC-Einführung, Aufgabenblatt S.1
- Anzahl korrigierbarer Ausfallstellen = dmin - 1 = 4 Ausfallstellen
- Code kann 4 Ausfallstellen korrigieren

### 3.4 Wie hoch ist die Coderate R des Codes?
**Quelle:** FEC-Einführung, Aufgabenblatt S.1
- Coderate R = k/n = 15/31 ≈ 0.48

### 3.5 Berechnen Sie die Blockfehlerwahrscheinlichkeit (ohne Korrektur) und die Restfehlerwahrscheinlichkeit bei Fehlerkorrektur und einer Übertragung über einen Binär-Kanal mit einer Bitfehlerwahrscheinlichkeit (BER) von Pb = 10−2.
- Pr = 3.7 * 10^-3
- ca. jeder 270. übertragene Block wird falsch korrigiert (Restfehler)


## 4. Fehlerkorrektur
gegeben ist folgender Kanalcode für die vier Zeichen A-D:
Zeichen     Kanalcode
A           000000
B           111000
C           000111
D           111111

### 4.1 Decodierprinzipien
**Quelle:** Blockcodierung, Folie 21-24

Es gibt drei wesentliche Decodierprinzipien:
- BMD (Bounded Minimum Distance): Begrenzt durch Minimaldistanz
- MLD (Maximum Likelihood): Wählt wahrscheinlichstes Codewort
- MAP (Maximum Aposteriori): Berücksichtigt zusätzlich Quellenstatistik

### 4.2 Wie groß ist die Minimaldistanz des Codes?
- Mitteldistanz beträgt dmin = 3 
(dmin ist der geringste unterschied zwischen zwei codeworten...A und B unterscheiden sich zb in den ersten 3 Stellen...A und D unterscheiden sich in allen 6 Stellen)

### 4.3 Wieviele Bitfehler lassen sich erkennen, wieviele unbekannte Fehler korrigieren und wieviele Ausfallstellen korrigieren?
Bitfehler: te = dmin - 1 = 2
korrigieren: tk = ((dmin-1)/2) = 1
Ausfallstellen: tA = 2

### 4.4 Wie würden Sie die folgenden gestörten Bitfolgen (Tabelle 2) beim MLD bzw. BMDDecodierprinzip korrigieren? (Hinweis: BMD– Bounded Minimum Distanz decodiert nur bis zur Minimaldistanz, MLD– Maximum Likelihood decodiert zum wahrscheinlichsten Codewort)
Empfangswort y      dH      x BMD       x MLD
100000              1       A           A
001111              1       C           C
101111              1       D           D
000111              0       C           C
101010              2       -           B


## 5. Praktische Codes
Gegeben ist ein (n,k,dmin)-Code als (127,64,21)-BCH-Code.

### 5.1 Welche Parameter können Sie aus dem BCH-Code ableiten?
- max Anzahl erkennbarer Fehler: tE = dmin - 1 = 20
- max Anzahl korrigierbarer Fehler: tK = ((dmin-1)/2) = 10
- Ausfallstelle: tA = 20
- Coderate: R = k/n = 0.5

### 5.2 Welchen Wert für dmin erhalten Sie aus der Singleton-Schranke?
- dmin = n-k+1 = 127-64+1 = 64 >> 21



# Übungsaufgaben Lineare Codes

## **1. Etwas Algebra: Galois-Felder**

Lineare Codes:
ein Codewort ist die Summe von Codewörtern

Vorteil:
es müssen nur die Basiscodewörter gespeichert werden
alle anderen Codewörter lassen sich mittels Vektoralgebra ermitteln

Wozu Galois-Felder?
Jedes Element eines Vektors ist Element eines Galois-Feld. Somit bleiben Additionen und andere Berechnungen auch im Galois-Feld.

### 1.1 **Bestimmen Sie die inversen Elemente bezüglich Addition und Multiplikation für GF(2) und GF(3)!**
- **GF(2):**
  - **Addition:** Das inverse Element zu 0 ist 0, zu 1 ist 1 (da 1 + 1 = 0).
  - **Multiplikation:** Das inverse Element zu 1 ist 1 (da 1 · 1 = 1).
- **GF(3):**
  - **Addition:** Das inverse Element zu 0 ist 0, zu 1 ist 2 (da 1 + 2 = 0), zu 2 ist 1 (da 2 + 1 = 0).
  - **Multiplikation:** Das inverse Element zu 1 ist 1 (da 1 · 1 = 1), zu 2 ist 2 (da 2 · 2 = 4 ≡ 1 mod 3).
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 5 und 6.

### 1.2 **Bestimmen Sie das neutrale Element bezüglich Addition und Multiplikation für GF(2) und GF(3)!**
- **GF(2):**
  - **Addition:** Das neutrale Element ist 0.
  - **Multiplikation:** Das neutrale Element ist 1.
- **GF(3):**
  - **Addition:** Das neutrale Element ist 0.
  - **Multiplikation:** Das neutrale Element ist 1.
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 5 und 6.

### 1.3 **Bestimmen Sie in GF(3): 2 + 2, 2 − 1, 2 · 2 und 1/2!**
- **2 + 2 = 1** (da 2 + 2 = 4 ≡ 1 mod 3)
- **2 − 1 = 1** (da 2 − 1 = 1)
- **2 · 2 = 1** (da 2 · 2 = 4 ≡ 1 mod 3)
- **1/2 = 2** (da 2 · 2 = 4 ≡ 1 mod 3)
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 6.


## **2. Linearer Binärcode**
Für lineare Codes gilt ci ⊕ cj ∈ C

### 2.1 **Bilden die folgenden Codeworte einen linearen Code?**
v1 = 100101 
v2 = 110011 
v3 = 111100 
v4 = 101010 
v5 = 001111 
v6 = 011001 
v7 = 010110 
v8 = 000000

Ansatz: XOR -> v1 + v2 = 100101 + 110011 = 010110 => v7

- **Antwort:** Ja, die Codeworte bilden einen linearen Code, da die Summe (XOR) zweier beliebiger Codeworte immer ein Codewort ergibt.
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 7.

### 2.2 **Geben Sie die Parameter (n, k) und die Minimal-Distanz des Codes an!**
- **n = 6** (Länge der Codeworte)
- **k = 3** (Anzahl der Basisvektoren)
- **Minimal-Distanz:** Die Minimal-Distanz ist der minimale Hamming-Abstand zwischen zwei Codeworten. Hier ist die Minimal-Distanz **2**.
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 8.

### 2.3 **Können folgende Codeworte als Basisvektoren des Codes dienen (lineare Unabhängigkeit)?**
v1 = 100101 
v2 = 110011 
v3 = 111100

- **Antwort:** Ja, die Vektoren v₁, v₂, v₃ sind linear unabhängig, da keiner der Vektoren als Linearkombination der anderen dargestellt werden kann.
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 14.

### 2.4 **Geben Sie die Gewichtsverteilung des Codes an!**
- **Gewichtsverteilung:** Die Gewichtsverteilung gibt an, wie viele Codeworte ein bestimmtes Hamming-Gewicht haben. Hier:
  - Gewicht 0: 1 Codewort
  - Gewicht 3: 4 Codeworte
  - Gewicht 4: 3 Codeworte
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 9.

### 2.5 **Erzeugen Sie aus den Basisvektoren die Generatormatrix eines systematischen Codes!**
  **Antwort Theo**
- **Generatormatrix G:**
  \[
  G = \begin{pmatrix}
  1 & 0 & 0 & 1 & 0 & 1 \\
  0 & 1 & 0 & 1 & 1 & 0 \\
  0 & 0 & 1 & 1 & 1 & 1 \\
  \end{pmatrix}
  \]

  **Antwort Discord**
  v1 :      (100101)
  
  v2 + v1:  (010110)
  
  v3 + v2:  (001111)
            (100101)
  
  G =       (010110)
            (001111)
 Erzeugt links die Einheitsmatrix und rechts P

- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 16.


## **3. Syndromdecodierung eines linearen Codes**
Gegeben ist ein linearer Code mit der Generatormatrix: 

G=    1 0 0 1 1
      0 1 1 1 0

### 3.1 **Listen Sie alle Codeworte auf und geben Sie die Codeparameter an!**
- **Codeworte:**  
  \[
  \{00000, 10011, 01110, 11101\}
  \]
- **Codeparameter:**  
  - **n = 5** (Länge der Codeworte)
  - **k = 2** (Anzahl der Basisvektoren)
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 14.

### 3.2 **Geben Sie die Prüfmatrix H an!**
- **Prüfmatrix H:**
  \[
  H = \begin{pmatrix}
  0 & 1 & 1 & 0 & 0 \\
  1 & 1 & 0 & 1 & 0 \\
  1 & 0 & 0 & 0 & 1 \\
  \end{pmatrix}
  \]
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 19.

### 3.3 **Führen Sie eine Nebenklassenzerlegung des Codes durch und wählen Sie geeignete Nebenklassenanführer!**
- **Nebenklassenzerlegung:**  
  - Nebenklasse 0: \{00000, 10011, 01110, 11101\}
  - Nebenklasse 1: \{00001, 10010, 01111, 11100\}
  - Nebenklasse 2: \{00010, 10001, 01100, 11111\}
  - Nebenklasse 3: \{00100, 10111, 01010, 11001\}
- **Nebenklassenanführer:** 00001, 00010, 00100
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 21.

### 3.4 **Stellen Sie die Syndromtabelle für eine Syndromdecodierung auf!**
- **Syndromtabelle:**
  \[
  \begin{array}{|c|c|}
  \hline
  \text{Syndrom} & \text{Fehlermuster} \\
  \hline
  000 & 00000 \\
  110 & 10000 \\
  011 & 01000 \\
  101 & 00100 \\
  \hline
  \end{array}
  \]
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 27.

### 3.5 **Decodieren Sie die Empfangsworte:**
- **y = (10000):** Syndrom = 110 → Fehlermuster = 10000 → decodiertes Codewort = 00000
- **y = (11101):** Syndrom = 000 → kein Fehler → decodiertes Codewort = 11101
- **y = (01011):** Syndrom = 101 → Fehlermuster = 00100 → decodiertes Codewort = 01111
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 27.



## **4. Mehrvalenter Code**
Gegeben ist ein linearer Code über F3 durch seine Generatormatrix 

G = 
1 0 1 1
0 1 1 2

### 4.1 **Welche Dimension und wieviele Codeworte hat der Code?**
- **Dimension:** k = 2
- **Anzahl der Codeworte:** 3² = 9 (3 weil F3 gegeben ist...bei wenn binär gegeben ist wäre es halt 2^2)
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 14.

### 4.2 **Wie groß ist seine minimale (Hamming-) Distanz?**
- **Minimale Distanz:** dₘᵢₙ = 3
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 8.

### 4.3 **Charakterisieren Sie die Fehler, die erkannt bzw. korrigiert werden können!**
- **Fehlererkennung:** dmin-1 = 3-1 = 2 -> Code kann bist zu zwei Fehler erkennen
- **Fehlerkorrektur:** (dmin-1)/2 = (3-1)/2 = 1 -> Code kann 1 Fehler korrigieren
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 8.

### 4.4 **Geben Sie eine Prüfmatrix an!**
- **Prüfmatrix H:**
  \[
  H = \begin{pmatrix}
  2 & 2 & 1 & 0 \\
  2 & 1 & 0 & 1 \\
  \end{pmatrix}
  \]
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 19.

### 4.5 **Testen Sie, ob die Worte [0112], [2212], [1202] gültige Codeworte sind!**
- **[0112]:** Syndrom = (0, 0) → gültig
- **[2212]:** Syndrom ≠ (0, 2) → ungültig
- **[1202]:** Syndrom = (0, 0) → gültig
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 24.

### 4.6 **Eine Generatormatrix**

G =
1 0 1 0
0 1 0 2



# Übungsaufgaben Zyklische Codes

## 1. Zyklischer Code
GegebenseiderfolgendebinäreCode (0000000),(1001110),(0011101),(1101001),(1110100),(0100111),(1010011),(0111010).

### 1.1 Ist der Code zyklisch?
**Antwort:**  
JA
Ein Code ist zyklisch, wenn jede zyklische Verschiebung eines Codewortes wieder ein Codewort ergibt. Dies ist eine grundlegende Eigenschaft von zyklischen Codes.  
**Quelle:** `it2-40-zykcodes_print.pdf`, Folie 4.

### 1.2 Wie groß ist die Minimaldistanz?
**Antwort:**
dmin = 4  
Die Minimaldistanz eines zyklischen Codes kann aus dem Minimalgewicht des Codes bestimmt werden. Das Minimalgewicht ist das kleinste Hamming-Gewicht aller Codewörter außer dem Nullwort.  
**Quelle:** `it2-35-lincodes_print.pdf`, Folie 8.

### 1.3 Geben Sie das Generatorpolynom an!
**Antwort:**
Generatorpolynom g(x) ist das von Null verschiedene Codepolynom kleinsten Grades, also g(x) = 1 + x + x^2 + x^4  
Das Generatorpolynom \( g(x) \) ist ein Polynom, das alle Codewörter des zyklischen Codes erzeugt. Es ist ein Teiler von \( x^n - 1 \) und hat den Grad \( n - k \), wobei \( n \) die Blocklänge und \( k \) die Anzahl der Informationsbits ist.  
**Quelle:** `it2-40-zykcodes_print.pdf`, Folie 9.

### 1.4 Stellen Sie die Codewörter als \( a(x)g(x) \) mit \( a(x) \in F_2[x] \) und Grad \( a(x) < 3 \) dar!
**Antwort:**  
Die Codewörter können als Produkt des Informationspolynoms \( a(x) \) und des Generatorpolynoms \( g(x) \) dargestellt werden. Dabei hat \( a(x) \) einen Grad kleiner als 3.
0*g(x)=0                    (0000000) 
1*g(x)=1+x+x^2+x^4          (1110100) 
x*g(x)=x+x^2+x^3+x^5        (0111010) 
(1+x)g(x)=1+x^3+x^4+x^5     (1001110) 
x^2g(x)=x^2+x^3+x4+x^6      (0011101) 
(1+x^2)g(x)=1+x+x^3+x^6     (1101001) 
(x+x^2)g(x)=x+x^4+x^5+x^6   (0100111) 
(1+x+x^2)g(x)=1+x^2+x^5+x^6 (1010011)
**Quelle:** `it2-40-zykcodes_print.pdf`, Folie 9.

### 1.5 Zeigen Sie, dass das Generatorpolynom ein Teiler von \( x^7 - 1 \) ist!
**Antwort:**  
Das Generatorpolynom \( g(x) \) muss ein Teiler von \( x^7 - 1 \) sein, da zyklische Codes durch Polynome erzeugt werden, die \( x^n - 1 \) teilen. Dies kann durch Polynomdivision überprüft werden.
Polynomendivision ergibt: (x^7-1):(x^4+x^2+x+1)=x^3+x+1 Rest 0  
**Quelle:** `it2-40-zykcodes_print.pdf`, Folie 9.

### 1.6 Geben Sie eine Generatormatrix an!
**Antwort:**  
Die Generatormatrix \( G \) eines zyklischen Codes kann aus dem Generatorpolynom \( g(x) \) abgeleitet werden. Die Zeilen der Generatormatrix sind die zyklischen Verschiebungen des Generatorpolynoms.

Die Vektoren assoziert mit g(x), xg(x) und x^2 g(x) bilden eine Basis, also: 
G=g(x), xg(x), x^2 g(x) 
1110100 
0111010 
0011101
**Quelle:** `it2-40-zykcodes_print.pdf`, Folie 10.


## 2. Codierung von CRC-Codes

Gegeben ist das Generatorpolynom g(x) = x^3 + x + 1

### 2.1 Wieviele Redundanzbits werden durch das gegebene Generatorpolynom erzeugt?
**Antwort**
m = Grad(g) = 3

### 2.2 Übertragen werden sollen Informationsblöcke mit jeweils 4Bit Länge. Geben Sie die Coderate (Verhältnis der Anzahl an Informationsbits zur Anzahl an Codebits) an!
**Antwort**
R = 4/7 = 0,57 es werden also pro übertragenem Bit nur 0,57 Informationsbits übertragen.

### 2.3 Berechnen Sie für das Informationswort 0101 das entsprechende Codewort.
**Antwort**
u′(x) = u(x)x^3 = x^4 + x^6 

x^6 + x^4 : x^3 + x + 1 = x^3 + 1 
x^6 + x^4 + x^3

x^3 
x^3 + x + 1

x + 1 = R 

c(x) = u′(x) + r(x) = 1 + x + x^4 + x^6 = 1100101


## 3. Fehlererkennungseigenschaften von CRC-Codes
### 3.1 Wieviele beliebig verteile Einzelfehler können durch einen CRC-Code sicher erkannt werden?
**Antwort**
Mit dmin = 4 können 3 Einzelfehler sicher erkannt werden

### 3.2 Geben Sie die Länge des Bündelfehlers aus Bild 1 an! Durch welchen CRC-Code kann dieses Fehlerereignis sicher erkannt werden?
**Antwort**
Bündelfehler der Länge 6, sicher erkennbar ab CRC-6
**Bild-Quelle:** `iaufg_crc_erg.pdf`, Folie 3.


## 4. Anwendung der CRC-Codes
In einem lokalen Netz (LAN) mit 100 Mbit/s wird mit einer Blocklänge von 1000 Bit unter Vollast gearbeitet. 
Bei im Durchschnitt jedem 50 000. Block treten Fehler auf, wobei die Hälfte der Blöcke von max. 3 Einzelfehlern betroffen ist und die andere Hälfte von Bündelfehlern mit einer Länge l > 100.

### 4.1 Geben Sie die Wahrscheinlichkeit an, das ein empfangener Block fehlerhaft ist!
**Antwort**
Wahrscheinlichkeit für einen Blockfehler: Pe = 1/50.000 = 2*10^-5

### 4.2 Berechnen Sie die Wahrscheinlichkeit, dass ein empfangener Block einen unerkannten Fehler bei Einsatz eines CRC8, CRC16 bzw. CRC32 hat!
**Antwort**
Wahrscheinlichkeit für das Versagen eines CRC-Codes bei Auftritt eines Bündelfehlers größerer Länge als m ist Pv = 2 m mit m der Anzahl an CRC-Bits. 

Nichterkannte Fehler (betrachtet werden nur die Bündelfehler, damit ist Pe = 10^-5 ) : 
CRC8: Pue = Pe*2^-8 = 3,9*10^-8 
CRC16: Pue = Pe*2^-16 = 1,5*10^-10 
CRC32: Pue = Pe*2^-32 = 2,3*10^-15

### 4.3 In welchen zeitlichen Abständen ist mit einem erkannten bzw. unerkannten Fehler bei der Übertragung zu rechnen?
**Antwort**
Blockrate bei Vollast: 100k Frames/s -> 2 Fehler pro 1s. 
Zeitlicher Abstand erkannter Fehler ca. 0,5s 
Zeitlicher Abstand von Bündelfehlern ca. 1s 

Zeitlicher Abstand unerkannter Fehler:
CRC8: 1s/2^-8 = 256s 
CRC16: 1s/2^-16 = 1092 min = 18h 
CRC32: 1s/2^-32 = 136 Jahre



# Galois-Felder

### 1. Welche Bedingungen müssen erfüllt sein, damit man von einem Galois-Feld bzw. endlichen Körper sprechen kann?
**Antwort:**  
Ein Galois-Feld (endlicher Körper) muss folgende Axiome erfüllen:  
1. Abgeschlossenheit bezüglich Addition und Multiplikation.  
2. Assoziativität von Addition und Multiplikation.  
3. Existenz eines neutralen Elements für Addition (0) und Multiplikation (1).  
4. Existenz von inversen Elementen für Addition und Multiplikation.  
5. Kommutativität von Addition und Multiplikation.  
6. Distributivgesetz: \( a \cdot (b + c) = a \cdot b + a \cdot c \).  
**Quelle:** `it2-50-galois_print.pdf`, Folie 4.

### 2. Was ist der Unterschied zwischen einem Primkörper und einem Erweiterungskörper?
**Antwort Discord und Folien**
- **Primkörper:** Im Fall von m = 1 spricht man auch von einem Primkörper 
- **Erweiterungskörper:** im Fall m > 1 von einem Erweiterungskörper 

**Antwort Theo**  
- **Primkörper:** Ein Galois-Feld mit \( p \) Elementen, wobei \( p \) eine Primzahl ist.  
- **Erweiterungskörper:** Ein Galois-Feld mit \( p^m \) Elementen, wobei \( m > 1 \) und \( p \) eine Primzahl ist. Erweiterungskörper werden durch Kombination von Primkörpern gebildet.  
**Quelle:** `it2-50-galois_print.pdf`, Folie 5.

### 3. Was ist ein primitives Element?
**Antwort Discord und Folien**
- In jedem Primkörper gibt es mindestens ein Element, dessen p−1 Potenzen alles Elemente des Primfeldes außer Null erzeugen 
- dieses Element wird als primitives Element α bezeichnet
- Eigenschaft: α^0 = α^(p−1) = 1

**Antwort Theo**  
Ein primitives Element ist ein Element eines Galois-Feldes, dessen Potenzen alle Elemente des Feldes außer Null erzeugen. Es hat die Ordnung \( p^m - 1 \).  
**Quelle:** `it2-50-galois_print.pdf`, Folie 9.

### 4. Was bedeutet die Bezeichnung Ordnung eines Elements?
**Antwort Discord und Folien**
- Die Ordnung eines Elements a aus GF(p) entspricht dem kleinsten Exponent r (r > 0), bei dem gilt: a^r = 1 mod p
**Quelle:** `it2-50-galois_print.pdf`, Folie 10.

### 5. Was ist ein irreduzibles Polynom?
**Antwort:**  
Ein Polynom \( p(x) \) mit Koeffizienten aus einem Galois-Feld heißt irreduzibel, wenn es nicht als Produkt von Polynomen kleineren Grades dargestellt werden kann. Es hat keine Nullstellen im zugrunde liegenden Körper.  
**Quelle:** `it2-50-galois_print.pdf`, Folie 11.

### 6. Was ist die Bedingung für die Existenz eines Erweiterungskörpers?
**Antwort:**  
- Für jede Primzahl \( p \) und jede natürliche Zahl \( m \) existiert mindestens ein irreduzibles Polynom vom Grad \( m \) über \( GF(p) \), das die Konstruktion eines Erweiterungskörpers \( GF(p^m) \) ermöglicht.
- irreduzibles Polynom hat somit keine Nullstelle in GF(p)
**Quelle:** `it2-50-galois_print.pdf`, Folie 13.

### 7. Was ist ein primitives Polynom?
**Antwort:**  
- Ein primitives Polynom ist ein irreduzibles Polynom, dessen Nullstelle ein primitives Element des Erweiterungskörpers ist. Es hat die Eigenschaft, dass seine Nullstellen alle Elemente des Körpers außer Null erzeugen.  
- beträgt der Zyklus der Polynomreste eines Polynoms vom Grad m gleich 2m − 1, dann wird es primitiv genannt
**Quelle:** `it2-50-galois_print.pdf`, Folie 17.

### 8. Was besagt der Fundamentalsatz der Algebra?
**Antwort:**  
- besagt, dass jedes Polynom m-ten Grades sich in genau m Teilpolynome erstem Grades, d.h. in m Linearfaktoren zerlegen lässt
**Quelle:** `it2-50-galois_print.pdf`, Folie 18.

### 9. Mittels welcher Methoden können Galois-Felder in Software abgebildet werden?
**Antwort:**  
Galois-Felder können in Software durch Lookup-Tabellen abgebildet werden, die die Umwandlung zwischen Potenz- und Polynomdarstellung ermöglichen. Addition erfolgt durch XOR-Operationen, Multiplikation durch Addition der Exponenten modulo \( p^m - 1 \).  
**Quelle:** `it2-50-galois_print.pdf`, Folie 32.



# Übungsaufgaben Galois-Felder

## 1. Primkörper

### 1.1 Prüfen Sie, ob alle Körpereigenschaften für F5 erfüllt sind.
**Antwort:**  
Ja, alle Körpereigenschaften sind für \( F_5 \) erfüllt:  
- Abgeschlossenheit, Assoziativität, Kommutativität für Addition und Multiplikation.  
- Existenz von neutralen Elementen (0 für Addition, 1 für Multiplikation).  
- Existenz von inversen Elementen für Addition und Multiplikation.  
- Distributivgesetz: \( a \cdot (b + c) = a \cdot b + a \cdot c \).  
**Quelle:** `it2-50-galois_print.pdf`, Folie 4.

### 1.2 Ermitteln Sie die primitiven Elemente aus obigem Galois-Feld!
**Antwort:**  
In \( F_5 \) sind die primitiven Elemente 2 und 3, da ihre Potenzen alle Elemente des Körpers außer Null erzeugen:  
- \( 2^1 = 2 \), \( 2^2 = 4 \), \( 2^3 = 3 \), \( 2^4 = 1 \).  
- \( 3^1 = 3 \), \( 3^2 = 4 \), \( 3^3 = 2 \), \( 3^4 = 1 \).  
**Quelle:** `it2-50-galois_print.pdf`, Folie 9.

### 1.3 Stellen Sie alle Elemente als Potenzen zum primitiven Element dar!
**Antwort:**  
Mit dem primitiven Element 2:  
- \( 2^0 = 1 \)  
- \( 2^1 = 2 \)  
- \( 2^2 = 4 \)  
- \( 2^3 = 3 \)  
- \( 2^4 = 1 \)
**Quelle:** `it2-50-galois_print.pdf`, Folie 9.


## 2. Primitive und irreduzible Polynome

### 2.1 Prüfen Sie, ob p(x) = x² + x + 1 irreduzibel über F2 ist!
**Antwort:**  
Ja, \( p(x) = x^2 + x + 1 \) ist irreduzibel über \( F_2 \), da es keine Nullstellen in \( F_2 \) hat und nicht in Polynome kleineren Grades zerlegt werden kann.  
**Quelle:** `it2-50-galois_print.pdf`, Folie 11.

### 2.2 Prüfen Sie, ob obiges Polynom primitiv über F2 ist!
**Antwort:**  
Ja, \( p(x) = x^2 + x + 1 \) ist primitiv über \( F_2 \), da seine Nullstelle ein primitives Element des Erweiterungskörpers \( F_4 \) ist.  
**Quelle:** `it2-50-galois_print.pdf`, Folie 17.


## 3. Erweiterungskörper

### 3.1 Existieren die folgenden Körper: F10, F15, F25?
**Antwort:**  
Primzahlen: 2,3,5,7,11,13,17,19,23...

- \( F_{10} \): Nein, da 10 keine Primzahlpotenz ist.  
- \( F_{15} \): Nein, da 15 keine Primzahlpotenz ist.  
- \( F_{25} \): Ja, da 25 = 5² eine Primzahlpotenz ist.  
**Quelle:** `it2-50-galois_print.pdf`, Folie 5.

### 3.2 Konstruieren Sie F8 unter Wahl des primitiven Polynoms p(x) = x³ + x² + 1 und stellen Sie dessen Elemente als Polynom in F2[x] und als Potenzen eines primitiven Elementes dar!
**Antwort:**  
Elemente von \( F_8 \) mit \( p(x) = x^3 + x^2 + 1 \):  
- \( 0 \): \( 0 \)  
- \( \alpha^0 \): \( 1 \)  
- \( \alpha^1 \): \( \alpha \)  
- \( \alpha^2 \): \( \alpha^2 \)  
- \( \alpha^3 \): \( \alpha^2 + 1 \)  
- \( \alpha^4 \): \( \alpha^2 + \alpha + 1 \)  
- \( \alpha^5 \): \( \alpha + 1 \)  
- \( \alpha^6 \): \( \alpha^2 + \alpha \)  
**Quelle:** `it2-50-galois_print.pdf`, Folie 28.

### 3.3 Führen Sie einige Operationen in F8 aus (Addition, Multiplikation, Finden von inversen Elementen z. B. (α³)⁻¹, Wurzel ziehen z. B. √α⁵)!
**Antwort:**  
- **Addition:** \( \alpha + \alpha^2 = \alpha^4 \)  
- **Multiplikation:** \( \alpha^3 \cdot \alpha^5 = \alpha^{8 \mod 7} = \alpha^1 \)  
- **Inverses von \( \alpha^3 \):** \( (\alpha^3)^{-1} = \alpha^4 \)  
- **Wurzel von \( \alpha^5 \):** \( \sqrt{\alpha^5} = \alpha^{5/2} = \alpha^6 \)  
**Quelle:** `it2-50-galois_print.pdf`, Folie 28.

### 3.4 Finden Sie alle primitiven Elemente in F8!
**Antwort:**  
Die primitiven Elemente in \( F_8 \) sind \( \alpha, \alpha^2, \alpha^3, \alpha^4, \alpha^5, \alpha^6 \), da ihre Potenzen alle Elemente außer Null erzeugen.  
**Quelle:** `it2-50-galois_print.pdf`, Folie 19.

### 3.5 Prüfen Sie Ihre Ergebnisse mittels GNU Octave unter Nutzung der gf-Funktion!  
**Antwort:**  
Beispiel in GNU Octave:  
```matlab
% Beispiel: Berechnung von α + α² in GF(8) mit x³ + x + 1 → 11
gf(2,3,11) + gf(4,3,11) = 6 → α + α²
```
**Quelle:** `it2-50-galois_print.pdf`, Folie 37.



# Reed-Solomon-Codes

### 1. Sind RS-Codes MDS-Codes?
**Antwort:**  
- Ja, Reed-Solomon-Codes (RS-Codes) sind MDS-Codes (Maximum Distance Separable Codes) 
- Sie erfüllen die Singleton-Schranke, d.h. die minimale Distanz \(d_{\text{min}}\) ist gleich \(n - k + 1\), wobei \(n\) die Blocklänge und \(k\) die Anzahl der Informationssymbole ist
- Dies bedeutet, dass RS-Codes die maximale mögliche Distanz für gegebene Parameter \(n\) und \(k\) erreichen
**Quelle:**  
Datei: `it2-60-rs-codes_print.pdf`, Folie 5

### 2. Es sollen 5 RTP-Pakte per RS-Codes in einer Gruppe geschützt werden. Drei fehlende Pakete sollen rekonstruiert werden können. Welche Parameter sollte für den RS-Code gewählt werden?
**Antwort:**  
- Um 3 fehlende Pakete rekonstruieren zu können, muss der RS-Code eine minimale Distanz \(d_{\text{min}} = 4\) haben (da \(d_{\text{min}} = t + 1\), wobei \(t\) die Anzahl der korrigierbaren Fehler ist)
- Für 5 RTP-Pakete (Informationssymbole) und 3 fehlende Pakete (Redundanzsymbole) ergibt sich ein RS-Code mit den Parametern \((n, k, d_{\text{min}}) = (8, 5, 4)\)
**Quelle:**  
Datei: `it2-60-rs-codes_print.pdf`, Folie 5

### 3. Welche Parameter für die Generatormatrix müssen Sie wählen, wenn Sie das o.g. Szenario per Matrix-Codierung bearbeiten wollen?
**Antwort:**  
- Für die Matrix-Codierung müssen Sie eine Generatormatrix \(G\) der Größe \(k \times n\) wählen, wobei \(k = 5\) (Anzahl der Informationspakete) und \(n = 8\) (Gesamtanzahl der Pakete, inklusive Redundanz). 
- Die Generatormatrix \(G\) wird verwendet, um die Informationspakete in codierte Pakete zu transformieren. 
- Die Matrix \(G\) sollte so konstruiert sein, dass sie die Eigenschaften des RS-Codes erfüllt, insbesondere die Fähigkeit, bis zu 3 fehlende Pakete zu korrigieren.
**Quelle:**  
Datei: `it2-60-rs-codes_print.pdf`, Folie 32-33



# Übungsaufgaben Reed-Solomon-Codes

## 1. RS-Code Codierung
### 1.1 Erzeugen Sie das Generatorpolynom für den RS-Code (7,5,3)₈ unter Nutzung des primitiven Polynoms p(x) = x³ + x² + 1 und w = 1.
**Antwort:**  
Das Generatorpolynom \(g(x)\) für den RS-Code (7,5,3)₈ mit \(w = 1\) wird durch die Nullstellen \(\alpha\) und \(\alpha^2\) definiert. Es ergibt sich zu:
\[
g(x) = (x - \alpha)(x - \alpha^2) = x^2 + \alpha x + \alpha^2 x + \alpha^3
\]
Unter Verwendung des primitiven Polynoms \(p(x) = x^3 + x^2 + 1\) und der Beziehung \(\alpha^3 = \alpha^2 + 1\) (da \(\alpha\) eine Nullstelle von \(p(x)\) ist), kann das Generatorpolynom weiter vereinfacht werden.
**Quelle:**  
Datei: `it2-60-rs-codes_print.pdf`, Folie 9

### 1.2 Wieviele Fehler und wieviele Ausfallstellen können mit diesem Code korrigiert werden?
**Antwort:**  
Der RS-Code (7,5,3)₈ hat eine minimale Distanz \(d_{\text{min}} = 3\). Damit können bis zu \(t = \frac{d_{\text{min}} - 1}{2} = 1\) Fehler korrigiert werden. Bei Ausfallstellen (d.h. bekannten Fehlerpositionen) können bis zu \(d_{\text{min}} - 1 = 2\) Ausfallstellen korrigiert werden.
**Quelle:**  
Datei: `it2-60-rs-codes_print.pdf`, Folie 5

### 1.3 Codieren Sie die Nachricht: u = (4 3 2 1 0)
**Antwort:**  
Erg.:
(6 7 4 3 2 1 0)

Die Nachricht \(u = (4, 3, 2, 1, 0)\) wird in ein Polynom \(u(x)\) umgewandelt:
\[
u(x) = 4x^4 + 3x^3 + 2x^2 + x + 0
\]
Das Codepolynom \(c(x)\) wird durch Multiplikation von \(u(x)\) mit \(x^{n-k}\) (hier \(x^2\)) und anschließender Division durch das Generatorpolynom \(g(x)\) berechnet. Der Rest \(r(x)\) wird dann zu \(u(x) \cdot x^{n-k}\) addiert, um das Codepolynom \(c(x)\) zu erhalten.
**Quelle:**  
Datei: `it2-60-rs-codes_print.pdf`, Folie 10-11

### 1.4 Prüfen Sie, ob α¹ eine Nullstelle des Codepolynoms ist.
**Antwort:**  
Um zu prüfen, ob \(\alpha^1\) eine Nullstelle des Codepolynoms \(c(x)\) ist, wird \(\alpha^1\) in \(c(x)\) eingesetzt. Wenn \(c(\alpha^1) = 0\) ist, dann ist \(\alpha^1\) eine Nullstelle. Dies kann durch Auswertung des Polynoms an der Stelle \(\alpha^1\) überprüft werden.
c(α) = α^6 +α^5 +α^4 +α^1+α^5+α^5 = 0 -> c(x) ist ein Codewort
**Quelle:**  
Datei: `it2-60-rs-codes_print.pdf`, Folie 12

### 1.5 Nutzen Sie GNU Octave zur Prüfung der obigen Codierung (Hinweis: Befehl `rsenc` aus der Communications Toolbox nutzbar).
**Antwort:**  
In GNU Octave kann die Codierung mit dem Befehl `rsenc` durchgeführt werden. Beispiel:
```octave
msg = gf([4 3 2 1 0], 3);  % Nachricht im Galois-Feld
code = rsenc(msg, 7, 5);   % Codierung mit RS-Code (7,5,3)
disp(code);                % Anzeige des Codeworts
```
Dieser Code erzeugt das Codewort für die Nachricht u=(4,3,2,1,0) u=(4,3,2,1,0).


## 2. Ausfallstellenkorrektur
### 2.1 Führen Sie eine Ausfallstellenkorrektur für den Empfangsvektor y = (X 1 1 1 1 1 X) unter Verwendung des RS-Codes aus der vorherigen Aufgabe durch!
**Antwort:** 
Für den Empfangsvektor y=(X,1,1,1,1,1,X) werden die Ausfallstellen an den Positionen 0 und 6 angenommen. Die Ausfallstellenkorrektur erfolgt durch Lösen eines linearen Gleichungssystems, das aus den Syndromgleichungen abgeleitet wird. Die Fehlerwerte e0 e0 und e6 e6 können durch die bekannten Ausfallstellen und die Syndromwerte berechnet werden.
**Quelle:**
Datei: `it2-60-rs-codes_print.pdf`, Folie 29-30

### 2.2 Schreiben Sie ein Octave-Programm zur Ausfallstellendecodierung und vergleichen Sie die Ergebnisse!

**Antwort:**
Ein Octave-Programm zur Ausfallstellendecodierung könnte wie folgt aussehen:
```octave
msg = gf([4 3 2 1 0], 3);  % Nachricht im Galois-Feld
code = rsenc(msg, 7, 5);   % Codierung mit RS-Code (7,5,3)

% Simuliere Ausfallstellen
code(1) = 0;  % Ausfallstelle an Position 0
code(7) = 0;  % Ausfallstelle an Position 6

% Decodierung mit Ausfallstellen
decoded_msg = rsdec(code, 7, 5);
disp(decoded_msg);  % Anzeige der decodierten Nachricht
```
Dieses Programm simuliert die Ausfallstellen und führt die Decodierung durch. Die Ergebnisse können mit der ursprünglichen Nachricht verglichen werden.

**Quelle:**
Datei: `it2-60-rs-codes_print.pdf`, Folie 43



# Online-Codes

### 1. Was ist unter dem Begriff Netzwerkcodierung zu verstehen?
**Antwort:**  
- Netzwerkcodierung ist eine Technik, bei der Datenpakete in einem Netzwerk nicht nur weitergeleitet, sondern auch kombiniert (kodiert) werden, um die Effizienz der Datenübertragung zu erhöhen 
- Im Gegensatz zur traditionellen Paketweiterleitung, bei der Pakete unverändert weitergeleitet werden, können bei der Netzwerkcodierung mehrere Pakete zu einem neuen Paket kombiniert werden 
- Dies ermöglicht eine höhere Auslastung der Netzwerkressourcen und eine verbesserte Fehlertoleranz
**Quelle:**  
Datei: `it2-70-online-codes_print.pdf`, Folie 6-7

### 2. Was ist der wesentliche Vorteil von ratenlosen Codes zu Codes mit einer festen Coderate?
**Antwort:**  
- Der wesentliche Vorteil von ratenlosen Codes (z.B. Online-Codes) gegenüber Codes mit einer festen Coderate ist, dass ratenlose Codes keine feste Anzahl von codierten Paketen benötigen, um die ursprünglichen Daten zu rekonstruieren. 
- Stattdessen können beliebige codierte Pakete verwendet werden, solange genügend davon empfangen wurden. Dies macht ratenlose Codes besonders robust gegenüber Paketverlusten und flexibel in dynamischen Netzwerken, da sie sich an die aktuellen Netzwerkbedingungen anpassen können.
- Bei ratenlosen Codes kann beliebig viel Redundanz erzeugt werden
**Quelle:**  
Datei: `it2-70-online-codes_print.pdf`, Folie 6-7

### 3. Überlegen Sie sich mögliche Anwendungen für ratenlose Codes!
**Antwort:**  
Mögliche Anwendungen für ratenlose Codes sind:
1. **Softwareverteilung in P2P-Netzen:** Ratenlose Codes ermöglichen eine effiziente Verteilung großer Dateien in Peer-to-Peer-Netzwerken, da sie robust gegenüber Paketverlusten sind und keine feste Anzahl von Paketen benötigen.
2. **Multicast-Streaming:** Bei der Übertragung von Multimedia-Inhalten an viele Empfänger können ratenlose Codes verwendet werden, um Paketverluste auszugleichen und die Übertragungsqualität zu verbessern.
3. **Datenarchivierung und -wiederherstellung:** Ratenlose Codes können in Backup-Systemen verwendet werden, um Daten sicher zu speichern und bei Bedarf wiederherzustellen, selbst wenn einige der gespeicherten Pakete beschädigt oder verloren sind.
4. **Satellitenkommunikation:** In Umgebungen mit hoher Latenz und Paketverlusten, wie z.B. bei der Satellitenkommunikation, können ratenlose Codes die Zuverlässigkeit der Datenübertragung erhöhen.
5. **ChipTan**
6. **Blockchain**
**Quelle:**  
Datei: `it2-70-online-codes_print.pdf`, Folie 5-6; 14-15