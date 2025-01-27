# Streaming

### 1. Wozu dient der Jitter-Puffer in einem Streaming-Empfänger?
*Quelle: Streaming-Verfahren, Folie 20*

Der Jitter-Puffer kompensiert Schwankungen in der Netzverzögerung bei der Übertragung von Streaming-Daten.

### 2. Wie erhält man die optimale Verzögerung des Puffers?
*Antwort nicht direkt in Folien zu finden*

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

### 13. Wofür dient das Attribut CSeq?
*Quelle: RTSP-Folien, Folie 10*

- Sequenznummer für Zuordnung von Request und Response
- Wird vom Client bei jeder Nachricht erhöht
- Server wiederholt die Nummer in der Antwort

### 14. Wie lautet ein minimaler OPTION- bzw. DESCRIBE-Request?
*Quelle: RTSP-Folien, Folie 18*

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

### 2. Welcher Kanal hat bei 50% Fehlern eine höhere Kanalkapazität?
**Quelle:** FEC-Einführung, Folie 6
Der BEC hat bei 50% Fehlern eine höhere Kanalkapazität:
- BEC: C = 1 - Pe = 0.5
- BSC: C = 1 + Pe·log2(Pe) + (1-Pe)·log2(1-Pe) ≈ 0

### 3. Welcher Kanal ist besser für die Modellierung der Übertragung auf Anwendungsebene geeignet und warum?
**Quelle:** FEC-Einführung, Folie 3
Der BEC ist besser geeignet, da er die IP-Übertragung (best effort) modelliert, bei der Pakete entweder korrekt ankommen oder verloren gehen. Der BSC modelliert eher die physikalische Schicht.

### 4. Warum ist des u.U. sinnvoll, den Fehlerschutz zusätzlich zur Bitübertragungsebene auch auf Anwendungsebene anzuwenden?
**Quelle:** Implizit aus FEC-RFCs
Weil Paketverluste auf Anwendungsebene andere Charakteristiken haben als Bitfehler auf der physikalischen Ebene. Ein Ende-zu-Ende Fehlerschutz kann Verluste auf allen Netzwerkebenen abdecken.

### 5. Welche Vorteile hat das FEC-Verfahren mittels Parity Check im Gegensatz zur Verdopplung des Datenstroms?
**Quelle:** FEC-Einführung, Folien 8-9
- Geringerer Overhead (50% vs. 100%)
- Kann bei geschickter Wahl der FEC-Pakete auch mehrere aufeinanderfolgende Paketverluste korrigieren

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
Pr = 1 - [(1-P)^3 + 3P(1-P)^2]
= 1 - [(0.99^3 + 30.010.99^2)]
= 1 - [0.970299 + 0.029403]
= 0.000298 ≈ 3E-4

### 11. Berechnen Sie die Blockfehlerwahrscheinlichkeit bei einer Übertragung über einen Binär-Kanal mit einer Bitfehlerwahrscheinlichkeit (BER) von Pb = 10^-2
**Quelle:** Blockcodierung, Folie 14
Die Wortfehlerwahrscheinlichkeit nach der Decodierung beträgt:
Pw ≤ Σ(n,d=t+1) (n,d) P^d_e · (1-Pe)^(n-d)






# RFC für FEC

### 1. **Warum ist es sinnvoll, eine FEC-Nutzung auf Anwendungsebene zu standardisieren?**
- **Antwort:** Die Standardisierung auf Anwendungsebene ermöglicht eine flexible und dynamische Anpassung der FEC-Parameter an die spezifischen Anforderungen der Medien- und Kanalcharakteristiken. Dies ist besonders wichtig für Multimedia-Anwendungen wie Audio und Video, bei denen die Netzwerkbedingungen variieren können. Zudem ist die Implementierung auf Anwendungsebene unabhängig von der darunterliegenden Netzwerkinfrastruktur, was die Kompatibilität mit verschiedenen Systemen und Protokollen gewährleistet.
- **Quelle:** `it2-25-fec-rfc_print.pdf`, Folie 5.

---

### 2. **Welche Vorteile bietet RFC 5109 im Gegensatz zu einer simplen statischen Nutzung von FEC?**
- **Antwort:** RFC 5109 bietet die Möglichkeit, die FEC-Parameter dynamisch anzupassen, was eine bessere Anpassung an die aktuellen Netzwerkbedingungen ermöglicht. Es unterstützt verschiedene Schutzlängen und -stufen sowie unterschiedliche Gruppengrößen. Zudem ist es vollständig kompatibel mit Empfängern, die keine FEC-Unterstützung haben, da die Medienpakete unverändert gesendet werden können.
- **Quelle:** `it2-25-fec-rfc_print.pdf`, Folie 4 und 5.

---

### 3. **Auf welchem FEC-Verfahren basiert RFC 5109?**
- **Antwort:** RFC 5109 basiert auf dem **XOR-Verfahren** (Exklusiv-Oder), das zur Erzeugung von FEC-Paketen verwendet wird. Dieses Verfahren ist einfach zu implementieren und effizient in der Fehlerkorrektur.
- **Quelle:** `it2-25-fec-rfc_print.pdf`, Folie 4.

---

### 4. **Für welche Anwendungen ist die Uneven Level Protection (ULP) sinnvoll?**
- **Antwort:** Die Uneven Level Protection (ULP) ist besonders sinnvoll für **Audio- und Videoanwendungen**, bei denen bestimmte Teile der Daten wichtiger sind als andere. Durch ULP können kritische Daten besser geschützt werden, während weniger wichtige Daten mit geringerer Redundanz übertragen werden.
- **Quelle:** `it2-25-fec-rfc_print.pdf`, Folie 7.

---

### 5. **Welche Gruppengrößen sind mit RFC 5109 möglich?**
- **Antwort:** RFC 5109 ermöglicht die Verwendung von **variablen Gruppengrößen**, die an die spezifischen Anforderungen der Anwendung angepasst werden können. Es gibt keine feste Begrenzung, aber die Gruppengröße wird typischerweise durch die Anzahl der zu schützenden Medienpakete und die gewünschte Redundanz bestimmt.
- **Quelle:** `it2-25-fec-rfc_print.pdf`, Folie 4 und 5.

---

### 6. **Wie kann der Beginn des nächsten Level-Headers ermittelt werden?**
- **Antwort:** Der Beginn des nächsten Level-Headers kann durch die **Länge des aktuellen Level-Payloads** ermittelt werden. Die Länge des Payloads wird im FEC-Level-Header angegeben, sodass der nächste Header direkt im Anschluss beginnt.
- **Quelle:** `it2-25-fec-rfc_print.pdf`, Folie 11.

---

### 7. **Was bedeutet SN-Base?**
- **Antwort:** **SN-Base** steht für die **Sequenznummer des ersten Medienpakets** in der Gruppe, die durch das FEC-Paket geschützt wird. Es ist die niedrigste Sequenznummer aller Medienpakete, die in der FEC-Gruppe enthalten sind.
- **Quelle:** `it2-25-fec-rfc_print.pdf`, Folie 10.

---





# Übungsaufgaben Grundlagen FEC

### 1. Bestimmen Sie die theoretisch minimale Verzögerung eines optimalen ARQ-Protokolls bei Auftritt eines Paketverlustes
**Quelle:** FEC-Einführung, Aufgabenblatt S.1
- Ende-zu-Ende-Verzögerung: TE-E = 140 ms
- Übertragungsverzögerungen und Verarbeitungsverzögerungen werden vernachlässigt
- Minimale Verzögerung: 2 * TE-E = 280 ms (für Erkennung des Verlusts und erneute Übertragung)

### 2. Geben Sie die Kanalkapazität der Verbindung an!
**Quelle:** FEC-Einführung, Aufgabenblatt S.1
- Daten: 100 Pakete/s, 1000 Bit pro Paket
- Kanalkapazität = 100 * 1000 = 100.000 Bit/s = 100 kBit/s

### 3. Wieviele Fehler kann ein Code mit (n,k,dmin) = (31,15,5) erkennen?
**Quelle:** FEC-Einführung, Aufgabenblatt S.1
- Anzahl erkennbarer Fehler = dmin - 1 = 4 Fehler
- Code kann 4 Fehler erkennen

### 4. Wieviele Fehler kann dieser Code korrigieren?
**Quelle:** FEC-Einführung, Aufgabenblatt S.1
- Anzahl korrigierbarer Fehler = ⌊(dmin-1)/2⌋ = ⌊4/2⌋ = 2 Fehler
- Code kann 2 Fehler korrigieren

### 5. Wieviele Ausfallstellen kann dieser Code korrigieren?
**Quelle:** FEC-Einführung, Aufgabenblatt S.1
- Anzahl korrigierbarer Ausfallstellen = dmin - 1 = 4 Ausfallstellen
- Code kann 4 Ausfallstellen korrigieren

### 6. Wie hoch ist die Coderate R des Codes?
**Quelle:** FEC-Einführung, Aufgabenblatt S.1
- Coderate R = k/n = 15/31 ≈ 0.48

## 4. Fehlerkorrektur

### 1. Decodierprinzipien
**Quelle:** Blockcodierung, Folie 21-24

Es gibt drei wesentliche Decodierprinzipien:
- BMD (Bounded Minimum Distance): Begrenzt durch Minimaldistanz
- MLD (Maximum Likelihood): Wählt wahrscheinlichstes Codewort
- MAP (Maximum Aposteriori): Berücksichtigt zusätzlich Quellenstatistik








# Übungsaufgaben Lineare Codes

---

## **1. Etwas Algebra: Galois-Felder**

### 1. **Bestimmen Sie die inversen Elemente bezüglich Addition und Multiplikation für GF(2) und GF(3)!**
- **GF(2):**
  - **Addition:** Das inverse Element zu 0 ist 0, zu 1 ist 1 (da 1 + 1 = 0).
  - **Multiplikation:** Das inverse Element zu 1 ist 1 (da 1 · 1 = 1).
- **GF(3):**
  - **Addition:** Das inverse Element zu 0 ist 0, zu 1 ist 2 (da 1 + 2 = 0), zu 2 ist 1 (da 2 + 1 = 0).
  - **Multiplikation:** Das inverse Element zu 1 ist 1 (da 1 · 1 = 1), zu 2 ist 2 (da 2 · 2 = 4 ≡ 1 mod 3).
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 5 und 6.

---

### 2. **Bestimmen Sie das neutrale Element bezüglich Addition und Multiplikation für GF(2) und GF(3)!**
- **GF(2):**
  - **Addition:** Das neutrale Element ist 0.
  - **Multiplikation:** Das neutrale Element ist 1.
- **GF(3):**
  - **Addition:** Das neutrale Element ist 0.
  - **Multiplikation:** Das neutrale Element ist 1.
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 5 und 6.

---

### 3. **Bestimmen Sie in GF(3): 2 + 2, 2 − 1, 2 · 2 und 1/2!**
- **2 + 2 = 1** (da 2 + 2 = 4 ≡ 1 mod 3)
- **2 − 1 = 1** (da 2 − 1 = 1)
- **2 · 2 = 1** (da 2 · 2 = 4 ≡ 1 mod 3)
- **1/2 = 2** (da 2 · 2 = 4 ≡ 1 mod 3)
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 6.

---

## **2. Linearer Binärcode**

### 1. **Bilden die folgenden Codeworte einen linearen Code?**
- **Antwort:** Ja, die Codeworte bilden einen linearen Code, da die Summe (XOR) zweier beliebiger Codeworte wieder ein Codewort ergibt.
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 7.

---

### 2. **Geben Sie die Parameter (n, k) und die Minimal-Distanz des Codes an!**
- **n = 6** (Länge der Codeworte)
- **k = 3** (Anzahl der Basisvektoren)
- **Minimal-Distanz:** Die Minimal-Distanz ist der minimale Hamming-Abstand zwischen zwei Codeworten. Hier ist die Minimal-Distanz **2**.
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 8.

---

### 3. **Können folgende Codeworte als Basisvektoren des Codes dienen (lineare Unabhängigkeit)?**
- **Antwort:** Ja, die Vektoren v₁, v₂, v₃ sind linear unabhängig, da keiner der Vektoren als Linearkombination der anderen dargestellt werden kann.
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 14.

---

### 4. **Geben Sie die Gewichtsverteilung des Codes an!**
- **Gewichtsverteilung:** Die Gewichtsverteilung gibt an, wie viele Codeworte ein bestimmtes Hamming-Gewicht haben. Hier:
  - Gewicht 0: 1 Codewort (000000)
  - Gewicht 2: 3 Codeworte
  - Gewicht 4: 3 Codeworte
  - Gewicht 6: 1 Codewort
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 9.

---

### 5. **Erzeugen Sie aus den Basisvektoren die Generatormatrix eines systematischen Codes!**
- **Generatormatrix G:**
  \[
  G = \begin{pmatrix}
  1 & 0 & 0 & 1 & 0 & 1 \\
  0 & 1 & 0 & 1 & 1 & 0 \\
  0 & 0 & 1 & 1 & 1 & 1 \\
  \end{pmatrix}
  \]
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 16.

---

## **3. Syndromdecodierung eines linearen Codes**

### 1. **Listen Sie alle Codeworte auf und geben Sie die Codeparameter an!**
- **Codeworte:**  
  \[
  \{00000, 10011, 01110, 11101\}
  \]
- **Codeparameter:**  
  - **n = 5** (Länge der Codeworte)
  - **k = 2** (Anzahl der Basisvektoren)
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 14.

---

### 2. **Geben Sie die Prüfmatrix H an!**
- **Prüfmatrix H:**
  \[
  H = \begin{pmatrix}
  1 & 1 & 1 & 0 & 0 \\
  1 & 0 & 0 & 1 & 0 \\
  0 & 1 & 0 & 0 & 1 \\
  \end{pmatrix}
  \]
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 19.

---

### 3. **Führen Sie eine Nebenklassenzerlegung des Codes durch und wählen Sie geeignete Nebenklassenanführer!**
- **Nebenklassenzerlegung:**  
  - Nebenklasse 0: \{00000, 10011, 01110, 11101\}
  - Nebenklasse 1: \{00001, 10010, 01111, 11100\}
  - Nebenklasse 2: \{00010, 10001, 01100, 11111\}
  - Nebenklasse 3: \{00100, 10111, 01010, 11001\}
- **Nebenklassenanführer:** 00001, 00010, 00100
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 21.

---

### 4. **Stellen Sie die Syndromtabelle für eine Syndromdecodierung auf!**
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

---

### 5. **Decodieren Sie die Empfangsworte:**
- **y = (10000):** Syndrom = 110 → Fehlermuster = 10000 → decodiertes Codewort = 00000
- **y = (11101):** Syndrom = 000 → kein Fehler → decodiertes Codewort = 11101
- **y = (01011):** Syndrom = 101 → Fehlermuster = 00100 → decodiertes Codewort = 01111
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 27.

---

## **4. Mehrvalenter Code**

### 1. **Welche Dimension und wieviele Codeworte hat der Code?**
- **Dimension:** k = 2
- **Anzahl der Codeworte:** 3² = 9
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 14.

---

### 2. **Wie groß ist seine minimale (Hamming-) Distanz?**
- **Minimale Distanz:** dₘᵢₙ = 2
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 8.

---

### 3. **Charakterisieren Sie die Fehler, die erkannt bzw. korrigiert werden können!**
- **Fehlererkennung:** Alle Fehler mit Gewicht ≤ 1 können erkannt werden.
- **Fehlerkorrektur:** Keine Fehlerkorrektur möglich, da dₘᵢₙ = 2.
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 8.

---

### 4. **Geben Sie eine Prüfmatrix an!**
- **Prüfmatrix H:**
  \[
  H = \begin{pmatrix}
  1 & 1 & 1 & 0 \\
  1 & 2 & 0 & 1 \\
  \end{pmatrix}
  \]
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 19.

---

### 5. **Testen Sie, ob die Worte [0112], [2212], [1202] gültige Codeworte sind!**
- **[0112]:** Syndrom = (0, 0) → gültig
- **[2212]:** Syndrom ≠ (0, 0) → ungültig
- **[1202]:** Syndrom = (0, 0) → gültig
- **Quelle:** `it2-35-lincodes_print.pdf`, Folie 24.

---







# Übungsaufgaben Zyklische Codes

## 1. Zyklischer Code

### 1. Ist der Code zyklisch?
**Antwort:**  
Ein Code ist zyklisch, wenn jede zyklische Verschiebung eines Codewortes wieder ein Codewort ergibt. Dies ist eine grundlegende Eigenschaft von zyklischen Codes.  
**Quelle:** `it2-40-zykcodes_print.pdf`, Folie 4.

---

### 2. Wie groß ist die Minimaldistanz?
**Antwort:**  
Die Minimaldistanz eines zyklischen Codes kann aus dem Minimalgewicht des Codes bestimmt werden. Das Minimalgewicht ist das kleinste Hamming-Gewicht aller Codewörter außer dem Nullwort.  
**Quelle:** `it2-35-lincodes_print.pdf`, Folie 8.

---

### 3. Geben Sie das Generatorpolynom an!
**Antwort:**  
Das Generatorpolynom \( g(x) \) ist ein Polynom, das alle Codewörter des zyklischen Codes erzeugt. Es ist ein Teiler von \( x^n - 1 \) und hat den Grad \( n - k \), wobei \( n \) die Blocklänge und \( k \) die Anzahl der Informationsbits ist.  
**Quelle:** `it2-40-zykcodes_print.pdf`, Folie 9.

---

### 4. Stellen Sie die Codewörter als \( a(x)g(x) \) mit \( a(x) \in F_2[x] \) und Grad \( a(x) < 3 \) dar!
**Antwort:**  
Die Codewörter können als Produkt des Informationspolynoms \( a(x) \) und des Generatorpolynoms \( g(x) \) dargestellt werden. Dabei hat \( a(x) \) einen Grad kleiner als 3.  
**Quelle:** `it2-40-zykcodes_print.pdf`, Folie 9.

---

### 5. Zeigen Sie, dass das Generatorpolynom ein Teiler von \( x^7 - 1 \) ist!
**Antwort:**  
Das Generatorpolynom \( g(x) \) muss ein Teiler von \( x^7 - 1 \) sein, da zyklische Codes durch Polynome erzeugt werden, die \( x^n - 1 \) teilen. Dies kann durch Polynomdivision überprüft werden.  
**Quelle:** `it2-40-zykcodes_print.pdf`, Folie 9.

---

### 6. Geben Sie eine Generatormatrix an!
**Antwort:**  
Die Generatormatrix \( G \) eines zyklischen Codes kann aus dem Generatorpolynom \( g(x) \) abgeleitet werden. Die Zeilen der Generatormatrix sind die zyklischen Verschiebungen des Generatorpolynoms.  
**Quelle:** `it2-40-zykcodes_print.pdf`, Folie 10.

---

## TODO:
- **Frage 4** könnte noch genauer beantwortet werden, indem ein konkretes Beispiel für \( a(x) \) und \( g(x) \) angegeben wird. Dies ist in den Folien nicht explizit dargestellt.
- **Frage 6** könnte durch ein konkretes Beispiel für eine Generatormatrix ergänzt werden, falls dies in den Folien nicht explizit vorhanden ist.






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

---

### 2. Was ist der Unterschied zwischen einem Primkörper und einem Erweiterungskörper?
**Antwort:**  
- **Primkörper:** Ein Galois-Feld mit \( p \) Elementen, wobei \( p \) eine Primzahl ist.  
- **Erweiterungskörper:** Ein Galois-Feld mit \( p^m \) Elementen, wobei \( m > 1 \) und \( p \) eine Primzahl ist. Erweiterungskörper werden durch Kombination von Primkörpern gebildet.  
**Quelle:** `it2-50-galois_print.pdf`, Folie 5.

---

### 3. Was ist ein primitives Element?
**Antwort:**  
Ein primitives Element ist ein Element eines Galois-Feldes, dessen Potenzen alle Elemente des Feldes außer Null erzeugen. Es hat die Ordnung \( p^m - 1 \).  
**Quelle:** `it2-50-galois_print.pdf`, Folie 9.

---

### 4. Was bedeutet die Bezeichnung Ordnung eines Elements?
**Antwort:**  
Die Ordnung eines Elements \( a \) in einem Galois-Feld ist die kleinste positive ganze Zahl \( k \), für die \( a^k = 1 \) gilt.  
**Quelle:** `it2-50-galois_print.pdf`, Folie 10.

---

### 5. Was ist ein irreduzibles Polynom?
**Antwort:**  
Ein Polynom \( p(x) \) mit Koeffizienten aus einem Galois-Feld heißt irreduzibel, wenn es nicht als Produkt von Polynomen kleineren Grades dargestellt werden kann. Es hat keine Nullstellen im zugrunde liegenden Körper.  
**Quelle:** `it2-50-galois_print.pdf`, Folie 11.

---

### 6. Was ist die Bedingung für die Existenz eines Erweiterungskörpers?
**Antwort:**  
Für jede Primzahl \( p \) und jede natürliche Zahl \( m \) existiert mindestens ein irreduzibles Polynom vom Grad \( m \) über \( GF(p) \), das die Konstruktion eines Erweiterungskörpers \( GF(p^m) \) ermöglicht.  
**Quelle:** `it2-50-galois_print.pdf`, Folie 13.

---

### 7. Was ist ein primitives Polynom?
**Antwort:**  
Ein primitives Polynom ist ein irreduzibles Polynom, dessen Nullstelle ein primitives Element des Erweiterungskörpers ist. Es hat die Eigenschaft, dass seine Nullstellen alle Elemente des Körpers außer Null erzeugen.  
**Quelle:** `it2-50-galois_print.pdf`, Folie 17.

---

### 8. Was besagt der Fundamentalsatz der Algebra?
**Antwort:**  
Der Fundamentalsatz der Algebra besagt, dass jedes Polynom \( m \)-ten Grades über einem Körper genau \( m \) Nullstellen (mit Vielfachheiten) in einem geeigneten Erweiterungskörper hat.  
**Quelle:** `it2-50-galois_print.pdf`, Folie 18.

---

### 9. Mittels welcher Methoden können Galois-Felder in Software abgebildet werden?
**Antwort:**  
Galois-Felder können in Software durch Lookup-Tabellen abgebildet werden, die die Umwandlung zwischen Potenz- und Polynomdarstellung ermöglichen. Addition erfolgt durch XOR-Operationen, Multiplikation durch Addition der Exponenten modulo \( p^m - 1 \).  
**Quelle:** `it2-50-galois_print.pdf`, Folie 32.





# Übungsaufgaben Galois-Felder

## 1. Primkörper

### 1. Prüfen Sie, ob alle Körpereigenschaften für F5 erfüllt sind.
**Antwort:**  
Ja, alle Körpereigenschaften sind für \( F_5 \) erfüllt:  
- Abgeschlossenheit, Assoziativität, Kommutativität für Addition und Multiplikation.  
- Existenz von neutralen Elementen (0 für Addition, 1 für Multiplikation).  
- Existenz von inversen Elementen für Addition und Multiplikation.  
- Distributivgesetz: \( a \cdot (b + c) = a \cdot b + a \cdot c \).  
**Quelle:** `it2-50-galois_print.pdf`, Folie 4.

---

### 2. Ermitteln Sie die primitiven Elemente aus obigem Galois-Feld!
**Antwort:**  
In \( F_5 \) sind die primitiven Elemente 2 und 3, da ihre Potenzen alle Elemente des Körpers außer Null erzeugen:  
- \( 2^1 = 2 \), \( 2^2 = 4 \), \( 2^3 = 3 \), \( 2^4 = 1 \).  
- \( 3^1 = 3 \), \( 3^2 = 4 \), \( 3^3 = 2 \), \( 3^4 = 1 \).  
**Quelle:** `it2-50-galois_print.pdf`, Folie 9.

---

### 3. Stellen Sie alle Elemente als Potenzen zum primitiven Element dar!
**Antwort:**  
Mit dem primitiven Element 2:  
- \( 2^0 = 1 \)  
- \( 2^1 = 2 \)  
- \( 2^2 = 4 \)  
- \( 2^3 = 3 \)  
- \( 2^4 = 1 \) (zyklisch).  
**Quelle:** `it2-50-galois_print.pdf`, Folie 9.

---

## 2. Primitive und irreduzible Polynome

### 1. Prüfen Sie, ob p(x) = x² + x + 1 irreduzibel über F2 ist!
**Antwort:**  
Ja, \( p(x) = x^2 + x + 1 \) ist irreduzibel über \( F_2 \), da es keine Nullstellen in \( F_2 \) hat und nicht in Polynome kleineren Grades zerlegt werden kann.  
**Quelle:** `it2-50-galois_print.pdf`, Folie 11.

---

### 2. Prüfen Sie, ob obiges Polynom primitiv über F2 ist!
**Antwort:**  
Ja, \( p(x) = x^2 + x + 1 \) ist primitiv über \( F_2 \), da seine Nullstelle ein primitives Element des Erweiterungskörpers \( F_4 \) ist.  
**Quelle:** `it2-50-galois_print.pdf`, Folie 17.

---

## 3. Erweiterungskörper

### 1. Existieren die folgenden Körper: F10, F15, F25?
**Antwort:**  
- \( F_{10} \): Nein, da 10 keine Primzahlpotenz ist.  
- \( F_{15} \): Nein, da 15 keine Primzahlpotenz ist.  
- \( F_{25} \): Ja, da 25 = 5² eine Primzahlpotenz ist.  
**Quelle:** `it2-50-galois_print.pdf`, Folie 5.

---

### 2. Konstruieren Sie F8 unter Wahl des primitiven Polynoms p(x) = x³ + x² + 1 und stellen Sie dessen Elemente als Polynom in F2[x] und als Potenzen eines primitiven Elementes dar!
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

---

### 3. Führen Sie einige Operationen in F8 aus (Addition, Multiplikation, Finden von inversen Elementen z. B. (α³)⁻¹, Wurzel ziehen z. B. √α⁵)!
**Antwort:**  
- **Addition:** \( \alpha + \alpha^2 = \alpha^4 \)  
- **Multiplikation:** \( \alpha^3 \cdot \alpha^5 = \alpha^{8 \mod 7} = \alpha^1 \)  
- **Inverses von \( \alpha^3 \):** \( (\alpha^3)^{-1} = \alpha^4 \)  
- **Wurzel von \( \alpha^5 \):** \( \sqrt{\alpha^5} = \alpha^{5/2} = \alpha^6 \)  
**Quelle:** `it2-50-galois_print.pdf`, Folie 28.

---

### 4. Finden Sie alle primitiven Elemente in F8!
**Antwort:**  
Die primitiven Elemente in \( F_8 \) sind \( \alpha, \alpha^2, \alpha^3, \alpha^4, \alpha^5, \alpha^6 \), da ihre Potenzen alle Elemente außer Null erzeugen.  
**Quelle:** `it2-50-galois_print.pdf`, Folie 19.

---

### 5. Prüfen Sie Ihre Ergebnisse mittels GNU Octave unter Nutzung der gf-Funktion!  
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
Ja, Reed-Solomon-Codes (RS-Codes) sind MDS-Codes (Maximum Distance Separable Codes). Sie erfüllen die Singleton-Schranke, d.h. die minimale Distanz \(d_{\text{min}}\) ist gleich \(n - k + 1\), wobei \(n\) die Blocklänge und \(k\) die Anzahl der Informationssymbole ist. Dies bedeutet, dass RS-Codes die maximale mögliche Distanz für gegebene Parameter \(n\) und \(k\) erreichen.

**Quelle:**  
Datei: `it2-60-rs-codes_print.pdf`, Folie 5

---

### 2. Es sollen 5 RTP-Pakte per RS-Codes in einer Gruppe geschützt werden. Drei fehlende Pakete sollen rekonstruiert werden können. Welche Parameter sollte für den RS-Code gewählt werden?

**Antwort:**  
Um 3 fehlende Pakete rekonstruieren zu können, muss der RS-Code eine minimale Distanz \(d_{\text{min}} = 4\) haben (da \(d_{\text{min}} = t + 1\), wobei \(t\) die Anzahl der korrigierbaren Fehler ist). Für 5 RTP-Pakete (Informationssymbole) und 3 fehlende Pakete (Redundanzsymbole) ergibt sich ein RS-Code mit den Parametern \((n, k, d_{\text{min}}) = (8, 5, 4)\).

**Quelle:**  
Datei: `it2-60-rs-codes_print.pdf`, Folie 5

---

### 3. Welche Parameter für die Generatormatrix müssen Sie wählen, wenn Sie das o.g. Szenario per Matrix-Codierung bearbeiten wollen?

**Antwort:**  
Für die Matrix-Codierung müssen Sie eine Generatormatrix \(G\) der Größe \(k \times n\) wählen, wobei \(k = 5\) (Anzahl der Informationspakete) und \(n = 8\) (Gesamtanzahl der Pakete, inklusive Redundanz). Die Generatormatrix \(G\) wird verwendet, um die Informationspakete in codierte Pakete zu transformieren. Die Matrix \(G\) sollte so konstruiert sein, dass sie die Eigenschaften des RS-Codes erfüllt, insbesondere die Fähigkeit, bis zu 3 fehlende Pakete zu korrigieren.

**Quelle:**  
Datei: `it2-60-rs-codes_print.pdf`, Folie 32-33

---








# Übungsaufgaben Reed-Solomon-Codes

## 1. RS-Code Codierung

### 1. Erzeugen Sie das Generatorpolynom für den RS-Code (7,5,3)₈ unter Nutzung des primitiven Polynoms p(x) = x³ + x² + 1 und w = 1.

**Antwort:**  
Das Generatorpolynom \(g(x)\) für den RS-Code (7,5,3)₈ mit \(w = 1\) wird durch die Nullstellen \(\alpha\) und \(\alpha^2\) definiert. Es ergibt sich zu:
\[
g(x) = (x - \alpha)(x - \alpha^2) = x^2 + (\alpha + \alpha^2)x + \alpha^3
\]
Unter Verwendung des primitiven Polynoms \(p(x) = x^3 + x^2 + 1\) und der Beziehung \(\alpha^3 = \alpha^2 + 1\) (da \(\alpha\) eine Nullstelle von \(p(x)\) ist), kann das Generatorpolynom weiter vereinfacht werden.

**Quelle:**  
Datei: `it2-60-rs-codes_print.pdf`, Folie 9

---

### 2. Wieviele Fehler und wieviele Ausfallstellen können mit diesem Code korrigiert werden?

**Antwort:**  
Der RS-Code (7,5,3)₈ hat eine minimale Distanz \(d_{\text{min}} = 3\). Damit können bis zu \(t = \frac{d_{\text{min}} - 1}{2} = 1\) Fehler korrigiert werden. Bei Ausfallstellen (d.h. bekannten Fehlerpositionen) können bis zu \(d_{\text{min}} - 1 = 2\) Ausfallstellen korrigiert werden.

**Quelle:**  
Datei: `it2-60-rs-codes_print.pdf`, Folie 5

---

### 3. Codieren Sie die Nachricht: u = (4 3 2 1 0)

**Antwort:**  
Die Nachricht \(u = (4, 3, 2, 1, 0)\) wird in ein Polynom \(u(x)\) umgewandelt:
\[
u(x) = 4x^4 + 3x^3 + 2x^2 + x + 0
\]
Das Codepolynom \(c(x)\) wird durch Multiplikation von \(u(x)\) mit \(x^{n-k}\) (hier \(x^2\)) und anschließender Division durch das Generatorpolynom \(g(x)\) berechnet. Der Rest \(r(x)\) wird dann zu \(u(x) \cdot x^{n-k}\) addiert, um das Codepolynom \(c(x)\) zu erhalten.

**Quelle:**  
Datei: `it2-60-rs-codes_print.pdf`, Folie 10-11

---

### 4. Prüfen Sie, ob α¹ eine Nullstelle des Codepolynoms ist.

**Antwort:**  
Um zu prüfen, ob \(\alpha^1\) eine Nullstelle des Codepolynoms \(c(x)\) ist, wird \(\alpha^1\) in \(c(x)\) eingesetzt. Wenn \(c(\alpha^1) = 0\) ist, dann ist \(\alpha^1\) eine Nullstelle. Dies kann durch Auswertung des Polynoms an der Stelle \(\alpha^1\) überprüft werden.

**Quelle:**  
Datei: `it2-60-rs-codes_print.pdf`, Folie 12

---

### 5. Nutzen Sie GNU Octave zur Prüfung der obigen Codierung (Hinweis: Befehl `rsenc` aus der Communications Toolbox nutzbar).

**Antwort:**  
In GNU Octave kann die Codierung mit dem Befehl `rsenc` durchgeführt werden. Beispiel:
```octave
msg = gf([4 3 2 1 0], 3);  % Nachricht im Galois-Feld
code = rsenc(msg, 7, 5);   % Codierung mit RS-Code (7,5,3)
disp(code);                % Anzeige des Codeworts
```
Dieser Code erzeugt das Codewort für die Nachricht u=(4,3,2,1,0) u=(4,3,2,1,0).

---

## 2. Ausfallstellenkorrektur

### 1. Führen Sie eine Ausfallstellenkorrektur für den Empfangsvektor y = (X 1 1 1 1 1 X) unter Verwendung des RS-Codes aus der vorherigen Aufgabe durch!

**Antwort:** 
Für den Empfangsvektor y=(X,1,1,1,1,1,X) y=(X,1,1,1,1,1,X) werden die Ausfallstellen an den Positionen 0 und 6 angenommen. Die Ausfallstellenkorrektur erfolgt durch Lösen eines linearen Gleichungssystems, das aus den Syndromgleichungen abgeleitet wird. Die Fehlerwerte e0 e0 und e6 e6 können durch die bekannten Ausfallstellen und die Syndromwerte berechnet werden.

**Quelle:**
Datei: `it2-60-rs-codes_print.pdf`, Folie 29-30

---

### 2. Schreiben Sie ein Octave-Programm zur Ausfallstellendecodierung und vergleichen Sie die Ergebnisse!

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

---





# Online-Codes

### 1. Was ist unter dem Begriff Netzwerkcodierung zu verstehen?

**Antwort:**  
Netzwerkcodierung ist eine Technik, bei der Datenpakete in einem Netzwerk nicht nur weitergeleitet, sondern auch kombiniert (kodiert) werden, um die Effizienz der Datenübertragung zu erhöhen. Im Gegensatz zur traditionellen Paketweiterleitung, bei der Pakete unverändert weitergeleitet werden, können bei der Netzwerkcodierung mehrere Pakete zu einem neuen Paket kombiniert werden. Dies ermöglicht eine höhere Auslastung der Netzwerkressourcen und eine verbesserte Fehlertoleranz.

**Quelle:**  
Datei: `it2-70-online-codes_print.pdf`, Folie 6-7

---

### 2. Was ist der wesentliche Vorteil von ratenlosen Codes zu Codes mit einer festen Coderate?

**Antwort:**  
Der wesentliche Vorteil von ratenlosen Codes (z.B. Online-Codes) gegenüber Codes mit einer festen Coderate ist, dass ratenlose Codes keine feste Anzahl von codierten Paketen benötigen, um die ursprünglichen Daten zu rekonstruieren. Stattdessen können beliebige codierte Pakete verwendet werden, solange genügend davon empfangen wurden. Dies macht ratenlose Codes besonders robust gegenüber Paketverlusten und flexibel in dynamischen Netzwerken, da sie sich an die aktuellen Netzwerkbedingungen anpassen können.

**Quelle:**  
Datei: `it2-70-online-codes_print.pdf`, Folie 6-7

---

### 3. Überlegen Sie sich mögliche Anwendungen für ratenlose Codes!

**Antwort:**  
Mögliche Anwendungen für ratenlose Codes sind:
1. **Softwareverteilung in P2P-Netzen:** Ratenlose Codes ermöglichen eine effiziente Verteilung großer Dateien in Peer-to-Peer-Netzwerken, da sie robust gegenüber Paketverlusten sind und keine feste Anzahl von Paketen benötigen.
2. **Multicast-Streaming:** Bei der Übertragung von Multimedia-Inhalten an viele Empfänger können ratenlose Codes verwendet werden, um Paketverluste auszugleichen und die Übertragungsqualität zu verbessern.
3. **Datenarchivierung und -wiederherstellung:** Ratenlose Codes können in Backup-Systemen verwendet werden, um Daten sicher zu speichern und bei Bedarf wiederherzustellen, selbst wenn einige der gespeicherten Pakete beschädigt oder verloren sind.
4. **Satellitenkommunikation:** In Umgebungen mit hoher Latenz und Paketverlusten, wie z.B. bei der Satellitenkommunikation, können ratenlose Codes die Zuverlässigkeit der Datenübertragung erhöhen.

**Quelle:**  
Datei: `it2-70-online-codes_print.pdf`, Folie 5-6

---