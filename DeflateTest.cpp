//
//  DeflateTest.cpp
//  jameo
//
//  Created by Uwe Runtemund on 15.09.15.
//  Copyright (c) 2015 Jameo Software. All rights reserved.
//

#include <algorithm>
#include "DeflateTest.h"
#include "core/Deflater.h"
#include "core/Inflater.h"

DeflateTest::DeflateTest(bool debug):Test(debug)
{
	SetName("Test Deflate");
}

void DeflateTest::DoTest()
{
	jm::String test=
	"Hat der alte Hexenmeister\n"
	"Sich doch einmal wegbegeben!\n"
	"Und nun sollen seine Geister\n"
	"Auch nach meinem Willen leben.\n"
	"Seine Wort und Werke\n"
	"Merkt ich und den Brauch,\n"
	"Und mit Geistesstärke\n"
	"Tu ich Wunder auch.\n"
	"Walle! walle\n"
	"Manche Strecke,\n"
	"Daß, zum Zwecke,\n"
	"Wasser fließe\n"
	"Und mit reichem, vollem Schwalle\n"
	"Zu dem Bade sich ergieße.\n"
	"Und nun komm, du alter Besen,\n"
	"Nimm die schlechten Lumpenhüllen!\n"
	"Bist schon lange Knecht gewesen:\n"
	"Nun erfülle meinen Willen!\n"
	"Auf zwei Beinen stehe,\n"
	"Oben sei ein Kopf,\n"
	"Eile nun und gehe\n"
	"Mit dem Wassertopf!\n"
	"Walle! walle\n"
	"Manche Strecke,\n"
	"Daß, zum Zwecke,\n"
	"Wasser fließe\n"
	"Und mit reichem, vollem Schwalle\n"
	"Zu dem Bade sich ergieße.";
	uint8* uncompressed=(uint8*)test.ToCString();
	uint32 uncompressedLength=0;
	while(uncompressed[uncompressedLength]!=0)uncompressedLength++;

	std::cout << "Uncompressed Length: " << uncompressedLength << std::endl;

	//Komprimieren
	uint8* compressed=NULL;
	uint32 compressedLength=0;
	jm::Deflater deflater = jm::Deflater();
	deflater.Reset();
	deflater.SetInput(uncompressed, uncompressedLength);
	deflater.Deflate(compressed, compressedLength);

	std::cout << "Compressed Length: " << compressedLength << std::endl;

	//Dekomprimieren
	uint8* restored=NULL;
	uint32 restoredLength=0;
	jm::Inflater inflater = jm::Inflater();
	inflater.Reset();
	inflater.SetInput(compressed, compressedLength);
	inflater.Inflate(restored, restoredLength);

	std::cout << "Restored Length: " << restoredLength << std::endl;

	//Vergleiche uncompressed und restored...
	TestEquals((int64)uncompressedLength,(int64)restoredLength,"Länge der Daten unterschiedlich.");

	uint32 l=std::min(uncompressedLength,restoredLength);

	for(uint32 a=0;a<l;a++)
	{
		TestEquals(uncompressed[a],restored[a],"Datenfehler in Kompression / Dekompression.");
	}

	delete[] uncompressed;
	delete[] compressed;
	delete[] restored;

	// Teste langen Code
	test=
	"0 g BT /Helvetica-Bold 16 Tf 56.6929 785.1969 Td (Jameo PDF\\055Distiller Testdokument) Tj ET\r\n"
	"BT /Helvetica 10 Tf 56.6929 756.8505 Td (Dieses Testdokument wurde ohne zus\\344tzliche Hilfsmittel aus dem PDF\\055Kit der Jameo Graphics Engine) Tj ET\r\n"
	"BT /Helvetica 10 Tf 56.6929 742.6772 Td (erzeugt\\056 Dieses Dokument enth\\344lt eine Vielzahl von Darstellungen\\054 die den gesamten Funktionsumfang) Tj ET\r\n"
	"BT /Helvetica 10 Tf 56.6929 728.504 Td (des Distillers testen und demonstrieren\\056) Tj ET\r\n"
	"BT /Helvetica-Bold 12 Tf 56.6929 688.819 Td (Jameo Distiller) Tj ET\r\n"
	"BT /Helvetica 10 Tf 56.6929 671.8111 Td (Distiller\\055Version:) Tj ET\r\n"
	"BT /Helvetica 10 Tf 170.0787 671.8111 Td (Jameo Graphics Library 0\\0567) Tj ET\r\n"
	"BT /Helvetica 10 Tf 56.6929 657.6379 Td (PDF\\055Version:) Tj ET\r\n"
	"BT /Helvetica 10 Tf 170.0787 657.6379 Td (1\\0567) Tj ET\r\n"
	"BT /Helvetica-Bold 12 Tf 56.6929 617.9528 Td (Standardschriften) Tj ET\r\n"
	"BT /Helvetica 10 Tf 56.6929 600.9449 Td (Das PDF\\055Format definiert insgesamt 14 Standardschriftarten\\054 die jeder Betracher garantieren muss\\056) Tj ET\r\n"
	"BT /Helvetica 10 Tf 56.6929 586.7717 Td (Diese Schriftarten brauchen also vom Distiller nicht in das Dokument eingebettet werden\\054 wenn Sie sie) Tj ET\r\n"
	"BT /Helvetica 10 Tf 56.6929 572.5985 Td (verwenden\\056 Die folgenden Zeilen sind jeweils in einer der Standardschriftarten geschrieben und demon\\055) Tj ET\r\n"
	"BT /Helvetica 10 Tf 56.6929 558.4253 Td (strieren die korrekte Umsetzung im Jameo PDF\\055Distiller\\056) Tj ET\r\n"
	"BT /Courier 10 Tf 56.6929 544.2521 Td (Courier: Zw\\366lf Boxk\\344mpfer jagen Viktor quer \\374ber den gro\\337en Sylter Deich\\056) Tj ET\r\n"
	"BT /Courier-Bold 10 Tf 56.6929 530.0788 Td (Courier\\055Bold: Zw\\366lf Boxk\\344mpfer jagen Viktor quer \\374ber den gro\\337en Sylter Deich\\056) Tj ET\r\n"
	"BT /Courier-Oblique 10 Tf 56.6929 515.9056 Td (Courier\\055Oblique: Zw\\366lf Boxk\\344mpfer jagen Viktor quer \\374ber den gro\\337en Sylter Deich\\056) Tj ET\r\n"
	"BT /Courier-BoldOblique 10 Tf 56.6929 501.7324 Td (Courier\\055BoldOblique: Zw\\366lf Boxk\\344mpfer jagen Viktor quer \\374ber den gro\\337en Deich\\056) Tj ET\r\n"
	"BT /Helvetica 10 Tf 56.6929 487.5591 Td (Helvetica: Zw\\366lf Boxk\\344mpfer jagen Viktor quer \\374ber den gro\\337en Sylter Deich\\056) Tj ET\r\n"
	"BT /Helvetica-Bold 10 Tf 56.6929 473.3859 Td (Helvetica\\055Bold: Zw\\366lf Boxk\\344mpfer jagen Viktor quer \\374ber den gro\\337en Sylter Deich\\056) Tj ET\r\n"
	"BT /Helvetica-Oblique 10 Tf 56.6929 459.2126 Td (Helvetica\\055Bold: Zw\\366lf Boxk\\344mpfer jagen Viktor quer \\374ber den gro\\337en Sylter Deich\\056) Tj ET\r\n"
	"BT /Helvetica-BoldOblique 10 Tf 56.6929 445.0394 Td (Helvetica\\055Bold: Zw\\366lf Boxk\\344mpfer jagen Viktor quer \\374ber den gro\\337en Sylter Deich\\056) Tj ET\r\n"
	"BT /Times-Roman 11 Tf 56.6929 430.8662 Td (Times\\055Roman: Zw\\366lf Boxk\\344mpfer jagen Viktor quer \\374ber den gro\\337en Sylter Deich\\056) Tj ET\r\n"
	"BT /Times-Bold 11 Tf 56.6929 416.693 Td (Times\\055Bold: Zw\\366lf Boxk\\344mpfer jagen Viktor quer \\374ber den gro\\337en Sylter Deich\\056) Tj ET\r\n"
	"BT /Times-Italic 11 Tf 56.6929 402.5197 Td (Times\\055Italic: Zw\\366lf Boxk\\344mpfer jagen Viktor quer \\374ber den gro\\337en Sylter Deich\\056) Tj ET\r\n"
	"BT /Times-BoldItalic 11 Tf 56.6929 388.3465 Td (Times\\055BoldItalic: Zw\\366lf Boxk\\344mpfer jagen Viktor quer \\374ber den gro\\337en Sylter Deich\\056) Tj ET\r\n"
	"BT /Helvetica 10 Tf 56.6929 374.1733 Td (Symbol: ) Tj ET\r\n"
	"BT /Symbol 11 Tf 56.6929 374.1733 Td (Ergois philous gignoske\\054 ma monon logois\\056) Tj ET\r\n"
	"BT /Helvetica 10 Tf 56.6929 360.0001 Td (ZapfDingbats: ) Tj ET\r\n"
	"BT /ZapfDingbats 11 Tf 133.9829 360.0001 Td (abcdefghijklmnopqrstuvwxyzABCDEFGH1234567890) Tj ET\r\n"
	"BT /Helvetica-Bold 12 Tf 56.6929 334.4883 Td (Zeichens\\344tze) Tj ET\r\n"
	"BT /Helvetica 10 Tf 56.6929 317.4803 Td (Die folgenden Tabellen listen ohne weiteren Kommentar alle Symbole der Symboltafeln f\\374r die Schriften) Tj ET\r\n"
	"BT /Helvetica 10 Tf 56.6929 303.3071 Td (Helvetica\\054 Symbol und ZapfDingats auf\\056 Die Helvetica ist nach \\042WinAnsiEncoding\\042 codiert\\056) Tj ET\r\n"
	"BT /Helvetica 10 Tf 63.7795 280.0356 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 74.9523 280.0356 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 89.1255 280.0356 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 103.2987 280.0356 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 117.472 280.0356 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 131.6452 280.0356 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 145.8184 280.0356 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 159.9916 280.0356 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 177.1654 280.0356 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 190.7282 280.0356 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 204.9015 280.0356 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 216.6845 280.0356 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 230.8578 280.0356 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 247.4211 280.0356 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 259.2043 280.0356 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 273.3775 280.0356 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 60.779 265.8624 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 74.9523 265.8624 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 89.1255 265.8624 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 103.2987 265.8624 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 117.472 265.8624 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 131.6452 265.8624 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 145.8184 265.8624 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 159.9916 265.8624 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 174.1649 265.8624 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 188.3381 265.8624 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 202.5113 265.8624 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 216.6845 265.8624 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 230.8578 265.8624 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 248.0315 265.8624 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 259.2043 265.8624 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 273.3775 265.8624 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 62.5295 251.6891 Td ( ) Tj ET\r\n"
	"BT /Helvetica 10 Tf 76.2877 251.6891 Td (\\041) Tj ET\r\n"
	"BT /Helvetica 10 Tf 89.1255 251.6891 Td (\\042) Tj ET\r\n"
	"BT /Helvetica 10 Tf 103.7992 251.6891 Td (\\043) Tj ET\r\n"
	"BT /Helvetica 10 Tf 117.472 251.6891 Td (\\044) Tj ET\r\n"
	"BT /Helvetica 10 Tf 130.4806 251.6891 Td (\\045) Tj ET\r\n"
	"BT /Helvetica 10 Tf 144.9297 251.6891 Td (\\046) Tj ET\r\n"
	"BT /Helvetica 10 Tf 159.9916 251.6891 Td (\\047) Tj ET\r\n"
	"BT /Helvetica 10 Tf 175.5003 251.6891 Td (\\050) Tj ET\r\n"
	"BT /Helvetica 10 Tf 189.6736 251.6891 Td (\\051) Tj ET\r\n"
	"BT /Helvetica 10 Tf 202.5113 251.6891 Td (\\052) Tj ET\r\n"
	"BT /Helvetica 10 Tf 216.9409 251.6891 Td (\\053) Tj ET\r\n"
	"BT /Helvetica 10 Tf 232.6083 251.6891 Td (\\054) Tj ET\r\n"
	"BT /Helvetica 10 Tf 245.031 251.6891 Td (\\055) Tj ET\r\n"
	"BT /Helvetica 10 Tf 260.9547 251.6891 Td (\\056) Tj ET\r\n"
	"BT /Helvetica 10 Tf 274.9888 251.6891 Td (\\057) Tj ET\r\n"
	"BT /Helvetica 10 Tf 61.2795 237.5159 Td (0) Tj ET\r\n"
	"BT /Helvetica 10 Tf 75.4528 237.5159 Td (1) Tj ET\r\n"
	"BT /Helvetica 10 Tf 89.626 237.5159 Td (2) Tj ET\r\n"
	"BT /Helvetica 10 Tf 103.7992 237.5159 Td (3) Tj ET\r\n"
	"BT /Helvetica 10 Tf 117.9724 237.5159 Td (4) Tj ET\r\n"
	"BT /Helvetica 10 Tf 132.1457 237.5159 Td (5) Tj ET\r\n"
	"BT /Helvetica 10 Tf 146.3189 237.5159 Td (6) Tj ET\r\n"
	"BT /Helvetica 10 Tf 160.4921 237.5159 Td (7) Tj ET\r\n"
	"BT /Helvetica 10 Tf 174.6654 237.5159 Td (8) Tj ET\r\n"
	"BT /Helvetica 10 Tf 188.8386 237.5159 Td (9) Tj ET\r\n"
	"BT /Helvetica 10 Tf 204.1227 237.5159 Td (:) Tj ET\r\n"
	"BT /Helvetica 10 Tf 218.2959 237.5159 Td (\\073) Tj ET\r\n"
	"BT /Helvetica 10 Tf 231.1141 237.5159 Td (\\074) Tj ET\r\n"
	"BT /Helvetica 10 Tf 245.2873 237.5159 Td (\\075) Tj ET\r\n"
	"BT /Helvetica 10 Tf 259.4606 237.5159 Td (\\076) Tj ET\r\n"
	"BT /Helvetica 10 Tf 274.1587 237.5159 Td (\\077) Tj ET\r\n"
	"BT /Helvetica 10 Tf 60.779 223.3427 Td (\\100) Tj ET\r\n"
	"BT /Helvetica 10 Tf 74.9523 223.3427 Td (A) Tj ET\r\n"
	"BT /Helvetica 10 Tf 89.1255 223.3427 Td (B) Tj ET\r\n"
	"BT /Helvetica 10 Tf 103.2987 223.3427 Td (C) Tj ET\r\n"
	"BT /Helvetica 10 Tf 117.472 223.3427 Td (D) Tj ET\r\n"
	"BT /Helvetica 10 Tf 131.6452 223.3427 Td (E) Tj ET\r\n"
	"BT /Helvetica 10 Tf 145.8184 223.3427 Td (F) Tj ET\r\n"
	"BT /Helvetica 10 Tf 159.9916 223.3427 Td (G) Tj ET\r\n"
	"BT /Helvetica 10 Tf 174.1649 223.3427 Td (H) Tj ET\r\n"
	"BT /Helvetica 10 Tf 188.3381 223.3427 Td (I) Tj ET\r\n"
	"BT /Helvetica 10 Tf 202.5113 223.3427 Td (J) Tj ET\r\n"
	"BT /Helvetica 10 Tf 216.6845 223.3427 Td (K) Tj ET\r\n"
	"BT /Helvetica 10 Tf 230.8578 223.3427 Td (L) Tj ET\r\n"
	"BT /Helvetica 10 Tf 245.031 223.3427 Td (M) Tj ET\r\n"
	"BT /Helvetica 10 Tf 259.2043 223.3427 Td (N) Tj ET\r\n"
	"BT /Helvetica 10 Tf 273.3775 223.3427 Td (O) Tj ET\r\n"
	"BT /Helvetica 10 Tf 60.779 209.1694 Td (P) Tj ET\r\n"
	"BT /Helvetica 10 Tf 74.9523 209.1694 Td (Q) Tj ET\r\n"
	"BT /Helvetica 10 Tf 89.1255 209.1694 Td (R) Tj ET\r\n"
	"BT /Helvetica 10 Tf 103.2987 209.1694 Td (S) Tj ET\r\n"
	"BT /Helvetica 10 Tf 117.472 209.1694 Td (T) Tj ET\r\n"
	"BT /Helvetica 10 Tf 131.6452 209.1694 Td (U) Tj ET\r\n"
	"BT /Helvetica 10 Tf 145.8184 209.1694 Td (V) Tj ET\r\n"
	"BT /Helvetica 10 Tf 159.9916 209.1694 Td (W) Tj ET\r\n"
	"BT /Helvetica 10 Tf 174.1649 209.1694 Td (X) Tj ET\r\n"
	"BT /Helvetica 10 Tf 188.3381 209.1694 Td (Y) Tj ET\r\n"
	"BT /Helvetica 10 Tf 202.5113 209.1694 Td (Z) Tj ET\r\n"
	"BT /Helvetica 10 Tf 218.02 209.1694 Td (\\133) Tj ET\r\n"
	"BT /Helvetica 10 Tf 230.8578 209.1694 Td (\\134) Tj ET\r\n"
	"BT /Helvetica 10 Tf 246.3665 209.1694 Td (\\135) Tj ET\r\n"
	"BT /Helvetica 10 Tf 259.2043 209.1694 Td (\\136) Tj ET\r\n"
	"BT /Helvetica 10 Tf 273.8779 209.1694 Td (\\137) Tj ET\r\n"
	"BT /Helvetica 10 Tf 60.779 194.9962 Td (\\140) Tj ET\r\n"
	"BT /Helvetica 10 Tf 74.9523 194.9962 Td (a) Tj ET\r\n"
	"BT /Helvetica 10 Tf 89.1255 194.9962 Td (b) Tj ET\r\n"
	"BT /Helvetica 10 Tf 103.2987 194.9962 Td (c) Tj ET\r\n"
	"BT /Helvetica 10 Tf 117.472 194.9962 Td (d) Tj ET\r\n"
	"BT /Helvetica 10 Tf 131.6452 194.9962 Td (e) Tj ET\r\n"
	"BT /Helvetica 10 Tf 145.8184 194.9962 Td (f) Tj ET\r\n"
	"BT /Helvetica 10 Tf 159.9916 194.9962 Td (g) Tj ET\r\n"
	"BT /Helvetica 10 Tf 174.1649 194.9962 Td (h) Tj ET\r\n"
	"BT /Helvetica 10 Tf 188.3381 194.9962 Td (i) Tj ET\r\n"
	"BT /Helvetica 10 Tf 202.5113 194.9962 Td (j) Tj ET\r\n"
	"BT /Helvetica 10 Tf 216.6845 194.9962 Td (k) Tj ET\r\n"
	"BT /Helvetica 10 Tf 230.8578 194.9962 Td (l) Tj ET\r\n"
	"BT /Helvetica 10 Tf 245.031 194.9962 Td (m) Tj ET\r\n"
	"BT /Helvetica 10 Tf 259.2043 194.9962 Td (n) Tj ET\r\n"
	"BT /Helvetica 10 Tf 273.3775 194.9962 Td (o) Tj ET\r\n"
	"BT /Helvetica 10 Tf 60.779 180.823 Td (p) Tj ET\r\n"
	"BT /Helvetica 10 Tf 74.9523 180.823 Td (q) Tj ET\r\n"
	"BT /Helvetica 10 Tf 89.1255 180.823 Td (r) Tj ET\r\n"
	"BT /Helvetica 10 Tf 103.2987 180.823 Td (s) Tj ET\r\n"
	"BT /Helvetica 10 Tf 117.472 180.823 Td (t) Tj ET\r\n"
	"BT /Helvetica 10 Tf 131.6452 180.823 Td (u) Tj ET\r\n"
	"BT /Helvetica 10 Tf 145.8184 180.823 Td (v) Tj ET\r\n"
	"BT /Helvetica 10 Tf 159.9916 180.823 Td (w) Tj ET\r\n"
	"BT /Helvetica 10 Tf 174.1649 180.823 Td (x) Tj ET\r\n"
	"BT /Helvetica 10 Tf 188.3381 180.823 Td (y) Tj ET\r\n"
	"BT /Helvetica 10 Tf 202.5113 180.823 Td (z) Tj ET\r\n"
	"BT /Helvetica 10 Tf 217.2851 180.823 Td (\\173) Tj ET\r\n"
	"BT /Helvetica 10 Tf 232.8573 180.823 Td (\\174) Tj ET\r\n"
	"BT /Helvetica 10 Tf 245.6316 180.823 Td (\\175) Tj ET\r\n"
	"BT /Helvetica 10 Tf 259.2043 180.823 Td (\\176) Tj ET\r\n"
	"BT /Helvetica 10 Tf 273.3775 180.823 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 60.779 166.6498 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 74.9523 166.6498 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 89.1255 166.6498 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 103.2987 166.6498 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 117.472 166.6498 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 131.6452 166.6498 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 145.8184 166.6498 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 159.9916 166.6498 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 174.1649 166.6498 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 188.3381 166.6498 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 202.5113 166.6498 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 216.6845 166.6498 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 230.8578 166.6498 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 245.031 166.6498 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 259.2043 166.6498 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 273.3775 166.6498 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 60.779 152.4766 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 74.9523 152.4766 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 89.1255 152.4766 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 103.2987 152.4766 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 117.472 152.4766 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 131.6452 152.4766 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 145.8184 152.4766 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 159.9916 152.4766 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 174.1649 152.4766 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 188.3381 152.4766 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 202.5113 152.4766 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 216.6845 152.4766 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 230.8578 152.4766 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 245.031 152.4766 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 259.2043 152.4766 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 273.3775 152.4766 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 60.779 138.3033 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 74.9523 138.3033 Td (\\241) Tj ET\r\n"
	"BT /Helvetica 10 Tf 89.1255 138.3033 Td (\\242) Tj ET\r\n"
	"BT /Helvetica 10 Tf 103.2987 138.3033 Td (\\243) Tj ET\r\n"
	"BT /Helvetica 10 Tf 117.472 138.3033 Td (\\244) Tj ET\r\n"
	"BT /Helvetica 10 Tf 131.6452 138.3033 Td (\\245) Tj ET\r\n"
	"BT /Helvetica 10 Tf 145.8184 138.3033 Td (\\246) Tj ET\r\n"
	"BT /Helvetica 10 Tf 159.9916 138.3033 Td (\\247) Tj ET\r\n"
	"BT /Helvetica 10 Tf 174.1649 138.3033 Td (\\250) Tj ET\r\n"
	"BT /Helvetica 10 Tf 187.3884 138.3033 Td (\\251) Tj ET\r\n"
	"BT /Helvetica 10 Tf 202.5113 138.3033 Td (\\252) Tj ET\r\n"
	"BT /Helvetica 10 Tf 216.6845 138.3033 Td (\\253) Tj ET\r\n"
	"BT /Helvetica 10 Tf 230.2938 138.3033 Td (\\254) Tj ET\r\n"
	"BT /Helvetica 10 Tf 245.031 138.3033 Td (\\225) Tj ET\r\n"
	"BT /Helvetica 10 Tf 258.2545 138.3033 Td (\\256) Tj ET\r\n"
	"BT /Helvetica 10 Tf 273.3775 138.3033 Td (\\257) Tj ET\r\n"
	"BT /Helvetica 10 Tf 61.78 124.1301 Td (\\260) Tj ET\r\n"
	"BT /Helvetica 10 Tf 75.2086 124.1301 Td (\\261) Tj ET\r\n"
	"BT /Helvetica 10 Tf 89.1255 124.1301 Td (\\262) Tj ET\r\n"
	"BT /Helvetica 10 Tf 103.2987 124.1301 Td (\\263) Tj ET\r\n"
	"BT /Helvetica 10 Tf 117.472 124.1301 Td (\\264) Tj ET\r\n"
	"BT /Helvetica 10 Tf 131.6452 124.1301 Td (\\265) Tj ET\r\n"
	"BT /Helvetica 10 Tf 145.8184 124.1301 Td (\\266) Tj ET\r\n"
	"BT /Helvetica 10 Tf 159.9916 124.1301 Td (\\267) Tj ET\r\n"
	"BT /Helvetica 10 Tf 174.1649 124.1301 Td (\\270) Tj ET\r\n"
	"BT /Helvetica 10 Tf 188.3381 124.1301 Td (\\271) Tj ET\r\n"
	"BT /Helvetica 10 Tf 202.5113 124.1301 Td (\\272) Tj ET\r\n"
	"BT /Helvetica 10 Tf 216.6845 124.1301 Td (\\273) Tj ET\r\n"
	"BT /Helvetica 10 Tf 230.8578 124.1301 Td (\\274) Tj ET\r\n"
	"BT /Helvetica 10 Tf 245.031 124.1301 Td (\\275) Tj ET\r\n"
	"BT /Helvetica 10 Tf 259.2043 124.1301 Td (\\276) Tj ET\r\n"
	"BT /Helvetica 10 Tf 273.3775 124.1301 Td (\\277) Tj ET\r\n"
	"BT /Helvetica 10 Tf 60.779 109.9568 Td (\\300) Tj ET\r\n"
	"BT /Helvetica 10 Tf 74.9523 109.9568 Td (\\301) Tj ET\r\n"
	"BT /Helvetica 10 Tf 89.1255 109.9568 Td (\\302) Tj ET\r\n"
	"BT /Helvetica 10 Tf 103.2987 109.9568 Td (\\303) Tj ET\r\n"
	"BT /Helvetica 10 Tf 117.472 109.9568 Td (\\304) Tj ET\r\n"
	"BT /Helvetica 10 Tf 131.6452 109.9568 Td (\\305) Tj ET\r\n"
	"BT /Helvetica 10 Tf 145.8184 109.9568 Td (\\306) Tj ET\r\n"
	"BT /Helvetica 10 Tf 159.9916 109.9568 Td (\\307) Tj ET\r\n"
	"BT /Helvetica 10 Tf 174.1649 109.9568 Td (\\310) Tj ET\r\n"
	"BT /Helvetica 10 Tf 188.3381 109.9568 Td (\\311) Tj ET\r\n"
	"BT /Helvetica 10 Tf 202.5113 109.9568 Td (\\312) Tj ET\r\n"
	"BT /Helvetica 10 Tf 216.6845 109.9568 Td (\\313) Tj ET\r\n"
	"BT /Helvetica 10 Tf 230.8578 109.9568 Td (\\314) Tj ET\r\n"
	"BT /Helvetica 10 Tf 245.031 109.9568 Td (\\315) Tj ET\r\n"
	"BT /Helvetica 10 Tf 259.2043 109.9568 Td (\\316) Tj ET\r\n"
	"BT /Helvetica 10 Tf 273.3775 109.9568 Td (\\317) Tj ET\r\n"
	"BT /Helvetica 10 Tf 60.779 95.7836 Td (\\320) Tj ET\r\n"
	"BT /Helvetica 10 Tf 74.9523 95.7836 Td (\\321) Tj ET\r\n"
	"BT /Helvetica 10 Tf 89.1255 95.7836 Td (\\322) Tj ET\r\n"
	"BT /Helvetica 10 Tf 103.2987 95.7836 Td (\\323) Tj ET\r\n"
	"BT /Helvetica 10 Tf 117.472 95.7836 Td (\\324) Tj ET\r\n"
	"BT /Helvetica 10 Tf 131.6452 95.7836 Td (\\325) Tj ET\r\n"
	"BT /Helvetica 10 Tf 145.8184 95.7836 Td (\\326) Tj ET\r\n"
	"BT /Helvetica 10 Tf 160.248 95.7836 Td (\\327) Tj ET\r\n"
	"BT /Helvetica 10 Tf 174.1649 95.7836 Td (\\330) Tj ET\r\n"
	"BT /Helvetica 10 Tf 188.3381 95.7836 Td (\\331) Tj ET\r\n"
	"BT /Helvetica 10 Tf 202.5113 95.7836 Td (\\332) Tj ET\r\n"
	"BT /Helvetica 10 Tf 216.6845 95.7836 Td (\\333) Tj ET\r\n"
	"BT /Helvetica 10 Tf 230.8578 95.7836 Td (\\334) Tj ET\r\n"
	"BT /Helvetica 10 Tf 245.031 95.7836 Td (\\335) Tj ET\r\n"
	"BT /Helvetica 10 Tf 259.2043 95.7836 Td (\\336) Tj ET\r\n"
	"BT /Helvetica 10 Tf 273.3775 95.7836 Td (\\337) Tj ET\r\n"
	"BT /Helvetica 10 Tf 60.779 81.6104 Td (\\340) Tj ET\r\n"
	"BT /Helvetica 10 Tf 74.9523 81.6104 Td (\\341) Tj ET\r\n"
	"BT /Helvetica 10 Tf 89.1255 81.6104 Td (\\342) Tj ET\r\n"
	"BT /Helvetica 10 Tf 103.2987 81.6104 Td (\\343) Tj ET\r\n"
	"BT /Helvetica 10 Tf 117.472 81.6104 Td (\\344) Tj ET\r\n"
	"BT /Helvetica 10 Tf 131.6452 81.6104 Td (\\345) Tj ET\r\n"
	"BT /Helvetica 10 Tf 145.8184 81.6104 Td (\\346) Tj ET\r\n"
	"BT /Helvetica 10 Tf 159.9916 81.6104 Td (\\347) Tj ET\r\n"
	"BT /Helvetica 10 Tf 174.1649 81.6104 Td (\\350) Tj ET\r\n"
	"BT /Helvetica 10 Tf 188.3381 81.6104 Td (\\351) Tj ET\r\n"
	"BT /Helvetica 10 Tf 202.5113 81.6104 Td (\\352) Tj ET\r\n"
	"BT /Helvetica 10 Tf 216.6845 81.6104 Td (\\353) Tj ET\r\n"
	"BT /Helvetica 10 Tf 230.8578 81.6104 Td (\\354) Tj ET\r\n"
	"BT /Helvetica 10 Tf 245.031 81.6104 Td (\\355) Tj ET\r\n"
	"BT /Helvetica 10 Tf 259.2043 81.6104 Td (\\356) Tj ET\r\n"
	"BT /Helvetica 10 Tf 273.3775 81.6104 Td (\\357) Tj ET\r\n"
	"BT /Helvetica 10 Tf 60.779 67.4372 Td (\\360) Tj ET\r\n"
	"BT /Helvetica 10 Tf 74.9523 67.4372 Td (\\361) Tj ET\r\n"
	"BT /Helvetica 10 Tf 89.1255 67.4372 Td (\\362) Tj ET\r\n"
	"BT /Helvetica 10 Tf 103.2987 67.4372 Td (\\363) Tj ET\r\n"
	"BT /Helvetica 10 Tf 117.472 67.4372 Td (\\364) Tj ET\r\n"
	"BT /Helvetica 10 Tf 131.6452 67.4372 Td (\\365) Tj ET\r\n"
	"BT /Helvetica 10 Tf 145.8184 67.4372 Td (\\366) Tj ET\r\n"
	"BT /Helvetica 10 Tf 160.248 67.4372 Td (\\367) Tj ET\r\n"
	"BT /Helvetica 10 Tf 174.1649 67.4372 Td (\\370) Tj ET\r\n"
	"BT /Helvetica 10 Tf 188.3381 67.4372 Td (\\371) Tj ET\r\n"
	"BT /Helvetica 10 Tf 202.5113 67.4372 Td (\\372) Tj ET\r\n"
	"BT /Helvetica 10 Tf 216.6845 67.4372 Td (\\373) Tj ET\r\n"
	"BT /Helvetica 10 Tf 230.8578 67.4372 Td (\\374) Tj ET\r\n"
	"BT /Helvetica 10 Tf 245.031 67.4372 Td (\\375) Tj ET\r\n"
	"BT /Helvetica 10 Tf 259.2043 67.4372 Td (\\376) Tj ET\r\n"
	"BT /Helvetica 10 Tf 273.3775 67.4372 Td (\\377) Tj ET\r\n"
	"0.1969 w 56.6929 289.1339 m 56.6929 62.3622 l 70.8661 289.1339 m 70.8661 62.3622 l 85.0394 289.1339 m 85.0394 62.3622 l 99.2126 289.1339 m 99.2126 62.3622 l 113.3858 289.1339 m 113.3858 62.3622 l 127.5591 289.1339 m 127.5591 62.3622 l 141.7323 289.1339 m 141.7323 62.3622 l 155.9055 289.1339 m 155.9055 62.3622 l 170.0787 289.1339 m 170.0787 62.3622 l 184.252 289.1339 m 184.252 62.3622 l 198.4252 289.1339 m 198.4252 62.3622 l 212.5984 289.1339 m 212.5984 62.3622 l 226.7717 289.1339 m 226.7717 62.3622 l 240.9449 289.1339 m 240.9449 62.3622 l 255.1181 289.1339 m 255.1181 62.3622 l 269.2914 289.1339 m 269.2914 62.3622 l 283.4646 289.1339 m 283.4646 62.3622 l 56.6929 289.1339 m 283.4646 289.1339 l 56.6929 274.9607 m 283.4646 274.9607 l 56.6929 260.7875 m 283.4646 260.7875 l 56.6929 246.6143 m 283.4646 246.6143 l 56.6929 232.441 m 283.4646 232.441 l 56.6929 218.2678 m 283.4646 218.2678 l 56.6929 204.0945 m 283.4646 204.0945 l 56.6929 189.9213 m 283.4646 189.9213 l 56.6929 175.7481 m 283.4646 175.7481 l 56.6929 161.5749 m 283.4646 161.5749 l 56.6929 147.4016 m 283.4646 147.4016 l 56.6929 133.2284 m 283.4646 133.2284 l 56.6929 119.0552 m 283.4646 119.0552 l 56.6929 104.882 m 283.4646 104.882 l 56.6929 90.7087 m 283.4646 90.7087 l 56.6929 76.5355 m 283.4646 76.5355 l 56.6929 62.3622 m 283.4646 62.3622 l  S"
	"BT /Symbol 11 Tf 318.8976 279.8344 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 329.7703 279.8344 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 343.9435 279.8344 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 358.1168 279.8344 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 372.29 279.8344 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 386.4632 279.8344 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 400.6364 279.8344 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 414.8097 279.8344 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 432.2835 279.8344 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 445.7853 279.8344 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 459.9585 279.8344 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 471.5026 279.8344 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 485.6758 279.8344 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 502.4782 279.8344 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 514.0223 279.8344 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 528.1955 279.8344 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 315.5971 265.6612 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 329.7703 265.6612 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 343.9435 265.6612 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 358.1168 265.6612 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 372.29 265.6612 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 386.4632 265.6612 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 400.6364 265.6612 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 414.8097 265.6612 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 428.9829 265.6612 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 443.1561 265.6612 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 457.3294 265.6612 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 471.5026 265.6612 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 485.6758 265.6612 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 503.1496 265.6612 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 514.0223 265.6612 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 528.1955 265.6612 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 317.5226 251.488 Td ( ) Tj ET\r\n"
	"BT /Symbol 11 Tf 331.2393 251.488 Td (\\041) Tj ET\r\n"
	"BT /Symbol 11 Tf 343.9435 251.488 Td (\\042) Tj ET\r\n"
	"BT /Symbol 11 Tf 358.6673 251.488 Td (\\043) Tj ET\r\n"
	"BT /Symbol 11 Tf 372.29 251.488 Td (\\044) Tj ET\r\n"
	"BT /Symbol 11 Tf 385.1822 251.488 Td (\\045) Tj ET\r\n"
	"BT /Symbol 11 Tf 399.6589 251.488 Td (\\046) Tj ET\r\n"
	"BT /Symbol 11 Tf 414.8097 251.488 Td (\\047) Tj ET\r\n"
	"BT /Symbol 11 Tf 430.4519 251.488 Td (\\050) Tj ET\r\n"
	"BT /Symbol 11 Tf 444.6252 251.488 Td (\\051) Tj ET\r\n"
	"BT /Symbol 11 Tf 457.3294 251.488 Td (\\052) Tj ET\r\n"
	"BT /Symbol 11 Tf 471.7846 251.488 Td (\\053) Tj ET\r\n"
	"BT /Symbol 11 Tf 487.6013 251.488 Td (\\054) Tj ET\r\n"
	"BT /Symbol 11 Tf 499.8491 251.488 Td (\\055) Tj ET\r\n"
	"BT /Symbol 11 Tf 515.9478 251.488 Td (\\056) Tj ET\r\n"
	"BT /Symbol 11 Tf 529.968 251.488 Td (\\057) Tj ET\r\n"
	"BT /Symbol 11 Tf 316.1476 237.3148 Td (0) Tj ET\r\n"
	"BT /Symbol 11 Tf 330.3209 237.3148 Td (1) Tj ET\r\n"
	"BT /Symbol 11 Tf 344.4941 237.3148 Td (2) Tj ET\r\n"
	"BT /Symbol 11 Tf 358.6673 237.3148 Td (3) Tj ET\r\n"
	"BT /Symbol 11 Tf 372.8406 237.3148 Td (4) Tj ET\r\n"
	"BT /Symbol 11 Tf 387.0138 237.3148 Td (5) Tj ET\r\n"
	"BT /Symbol 11 Tf 401.187 237.3148 Td (6) Tj ET\r\n"
	"BT /Symbol 11 Tf 415.3603 237.3148 Td (7) Tj ET\r\n"
	"BT /Symbol 11 Tf 429.5335 237.3148 Td (8) Tj ET\r\n"
	"BT /Symbol 11 Tf 443.7067 237.3148 Td (9) Tj ET\r\n"
	"BT /Symbol 11 Tf 459.1018 237.3148 Td (:) Tj ET\r\n"
	"BT /Symbol 11 Tf 473.2751 237.3148 Td (\\073) Tj ET\r\n"
	"BT /Symbol 11 Tf 485.9578 237.3148 Td (\\074) Tj ET\r\n"
	"BT /Symbol 11 Tf 500.1311 237.3148 Td (\\075) Tj ET\r\n"
	"BT /Symbol 11 Tf 514.3043 237.3148 Td (\\076) Tj ET\r\n"
	"BT /Symbol 11 Tf 529.0549 237.3148 Td (\\077) Tj ET\r\n"
	"BT /Symbol 11 Tf 315.5971 223.1415 Td (\\100) Tj ET\r\n"
	"BT /Symbol 11 Tf 329.7703 223.1415 Td (A) Tj ET\r\n"
	"BT /Symbol 11 Tf 343.9435 223.1415 Td (B) Tj ET\r\n"
	"BT /Symbol 11 Tf 358.1168 223.1415 Td (C) Tj ET\r\n"
	"BT /Symbol 11 Tf 372.29 223.1415 Td (D) Tj ET\r\n"
	"BT /Symbol 11 Tf 386.4632 223.1415 Td (E) Tj ET\r\n"
	"BT /Symbol 11 Tf 400.6364 223.1415 Td (F) Tj ET\r\n"
	"BT /Symbol 11 Tf 414.8097 223.1415 Td (G) Tj ET\r\n"
	"BT /Symbol 11 Tf 428.9829 223.1415 Td (H) Tj ET\r\n"
	"BT /Symbol 11 Tf 443.1561 223.1415 Td (I) Tj ET\r\n"
	"BT /Symbol 11 Tf 457.3294 223.1415 Td (J) Tj ET\r\n"
	"BT /Symbol 11 Tf 471.5026 223.1415 Td (K) Tj ET\r\n"
	"BT /Symbol 11 Tf 485.6758 223.1415 Td (L) Tj ET\r\n"
	"BT /Symbol 11 Tf 499.8491 223.1415 Td (M) Tj ET\r\n"
	"BT /Symbol 11 Tf 514.0223 223.1415 Td (N) Tj ET\r\n"
	"BT /Symbol 11 Tf 528.1955 223.1415 Td (O) Tj ET\r\n"
	"BT /Symbol 11 Tf 315.5971 208.9683 Td (P) Tj ET\r\n"
	"BT /Symbol 11 Tf 329.7703 208.9683 Td (Q) Tj ET\r\n"
	"BT /Symbol 11 Tf 343.9435 208.9683 Td (R) Tj ET\r\n"
	"BT /Symbol 11 Tf 358.1168 208.9683 Td (S) Tj ET\r\n"
	"BT /Symbol 11 Tf 372.29 208.9683 Td (T) Tj ET\r\n"
	"BT /Symbol 11 Tf 386.4632 208.9683 Td (U) Tj ET\r\n"
	"BT /Symbol 11 Tf 400.6364 208.9683 Td (V) Tj ET\r\n"
	"BT /Symbol 11 Tf 414.8097 208.9683 Td (W) Tj ET\r\n"
	"BT /Symbol 11 Tf 428.9829 208.9683 Td (X) Tj ET\r\n"
	"BT /Symbol 11 Tf 443.1561 208.9683 Td (Y) Tj ET\r\n"
	"BT /Symbol 11 Tf 457.3294 208.9683 Td (Z) Tj ET\r\n"
	"BT /Symbol 11 Tf 472.9716 208.9683 Td (\\133) Tj ET\r\n"
	"BT /Symbol 11 Tf 485.6758 208.9683 Td (\\134) Tj ET\r\n"
	"BT /Symbol 11 Tf 501.3181 208.9683 Td (\\135) Tj ET\r\n"
	"BT /Symbol 11 Tf 514.0223 208.9683 Td (\\136) Tj ET\r\n"
	"BT /Symbol 11 Tf 528.7461 208.9683 Td (\\137) Tj ET\r\n"
	"BT /Symbol 11 Tf 315.5971 194.795 Td (\\140) Tj ET\r\n"
	"BT /Symbol 11 Tf 329.7703 194.795 Td (a) Tj ET\r\n"
	"BT /Symbol 11 Tf 343.9435 194.795 Td (b) Tj ET\r\n"
	"BT /Symbol 11 Tf 358.1168 194.795 Td (c) Tj ET\r\n"
	"BT /Symbol 11 Tf 372.29 194.795 Td (d) Tj ET\r\n"
	"BT /Symbol 11 Tf 386.4632 194.795 Td (e) Tj ET\r\n"
	"BT /Symbol 11 Tf 400.6364 194.795 Td (f) Tj ET\r\n"
	"BT /Symbol 11 Tf 414.8097 194.795 Td (g) Tj ET\r\n"
	"BT /Symbol 11 Tf 428.9829 194.795 Td (h) Tj ET\r\n"
	"BT /Symbol 11 Tf 443.1561 194.795 Td (i) Tj ET\r\n"
	"BT /Symbol 11 Tf 457.3294 194.795 Td (j) Tj ET\r\n"
	"BT /Symbol 11 Tf 471.5026 194.795 Td (k) Tj ET\r\n"
	"BT /Symbol 11 Tf 485.6758 194.795 Td (l) Tj ET\r\n"
	"BT /Symbol 11 Tf 499.8491 194.795 Td (m) Tj ET\r\n"
	"BT /Symbol 11 Tf 514.0223 194.795 Td (n) Tj ET\r\n"
	"BT /Symbol 11 Tf 528.1955 194.795 Td (o) Tj ET\r\n"
	"BT /Symbol 11 Tf 315.5971 180.6218 Td (p) Tj ET\r\n"
	"BT /Symbol 11 Tf 329.7703 180.6218 Td (q) Tj ET\r\n"
	"BT /Symbol 11 Tf 343.9435 180.6218 Td (r) Tj ET\r\n"
	"BT /Symbol 11 Tf 358.1168 180.6218 Td (s) Tj ET\r\n"
	"BT /Symbol 11 Tf 372.29 180.6218 Td (t) Tj ET\r\n"
	"BT /Symbol 11 Tf 386.4632 180.6218 Td (u) Tj ET\r\n"
	"BT /Symbol 11 Tf 400.6364 180.6218 Td (v) Tj ET\r\n"
	"BT /Symbol 11 Tf 414.8097 180.6218 Td (w) Tj ET\r\n"
	"BT /Symbol 11 Tf 428.9829 180.6218 Td (x) Tj ET\r\n"
	"BT /Symbol 11 Tf 443.1561 180.6218 Td (y) Tj ET\r\n"
	"BT /Symbol 11 Tf 457.3294 180.6218 Td (z) Tj ET\r\n"
	"BT /Symbol 11 Tf 472.1633 180.6218 Td (\\173) Tj ET\r\n"
	"BT /Symbol 11 Tf 487.8753 180.6218 Td (\\174) Tj ET\r\n"
	"BT /Symbol 11 Tf 500.5097 180.6218 Td (\\175) Tj ET\r\n"
	"BT /Symbol 11 Tf 514.0223 180.6218 Td (\\176) Tj ET\r\n"
	"BT /Symbol 11 Tf 528.1955 180.6218 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 315.5971 166.4486 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 329.7703 166.4486 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 343.9435 166.4486 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 358.1168 166.4486 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 372.29 166.4486 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 386.4632 166.4486 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 400.6364 166.4486 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 414.8097 166.4486 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 428.9829 166.4486 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 443.1561 166.4486 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 457.3294 166.4486 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 471.5026 166.4486 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 485.6758 166.4486 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 499.8491 166.4486 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 514.0223 166.4486 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 528.1955 166.4486 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 315.5971 152.2754 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 329.7703 152.2754 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 343.9435 152.2754 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 358.1168 152.2754 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 372.29 152.2754 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 386.4632 152.2754 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 400.6364 152.2754 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 414.8097 152.2754 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 428.9829 152.2754 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 443.1561 152.2754 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 457.3294 152.2754 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 471.5026 152.2754 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 485.6758 152.2754 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 499.8491 152.2754 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 514.0223 152.2754 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 528.1955 152.2754 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 315.5971 138.1021 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 329.7703 138.1021 Td (\\241) Tj ET\r\n"
	"BT /Symbol 11 Tf 343.9435 138.1021 Td (\\242) Tj ET\r\n"
	"BT /Symbol 11 Tf 358.1168 138.1021 Td (\\243) Tj ET\r\n"
	"BT /Symbol 11 Tf 372.29 138.1021 Td (\\244) Tj ET\r\n"
	"BT /Symbol 11 Tf 386.4632 138.1021 Td (\\245) Tj ET\r\n"
	"BT /Symbol 11 Tf 400.6364 138.1021 Td (\\246) Tj ET\r\n"
	"BT /Symbol 11 Tf 414.8097 138.1021 Td (\\247) Tj ET\r\n"
	"BT /Symbol 11 Tf 428.9829 138.1021 Td (\\250) Tj ET\r\n"
	"BT /Symbol 11 Tf 442.1115 138.1021 Td (\\251) Tj ET\r\n"
	"BT /Symbol 11 Tf 457.3294 138.1021 Td (\\252) Tj ET\r\n"
	"BT /Symbol 11 Tf 471.5026 138.1021 Td (\\253) Tj ET\r\n"
	"BT /Symbol 11 Tf 485.0555 138.1021 Td (\\254) Tj ET\r\n"
	"BT /Symbol 11 Tf 499.8491 138.1021 Td (\\225) Tj ET\r\n"
	"BT /Symbol 11 Tf 512.9776 138.1021 Td (\\256) Tj ET\r\n"
	"BT /Symbol 11 Tf 528.1955 138.1021 Td (\\257) Tj ET\r\n"
	"BT /Symbol 11 Tf 316.6982 123.9289 Td (\\260) Tj ET\r\n"
	"BT /Symbol 11 Tf 330.0523 123.9289 Td (\\261) Tj ET\r\n"
	"BT /Symbol 11 Tf 343.9435 123.9289 Td (\\262) Tj ET\r\n"
	"BT /Symbol 11 Tf 358.1168 123.9289 Td (\\263) Tj ET\r\n"
	"BT /Symbol 11 Tf 372.29 123.9289 Td (\\264) Tj ET\r\n"
	"BT /Symbol 11 Tf 386.4632 123.9289 Td (\\265) Tj ET\r\n"
	"BT /Symbol 11 Tf 400.6364 123.9289 Td (\\266) Tj ET\r\n"
	"BT /Symbol 11 Tf 414.8097 123.9289 Td (\\267) Tj ET\r\n"
	"BT /Symbol 11 Tf 428.9829 123.9289 Td (\\270) Tj ET\r\n"
	"BT /Symbol 11 Tf 443.1561 123.9289 Td (\\271) Tj ET\r\n"
	"BT /Symbol 11 Tf 457.3294 123.9289 Td (\\272) Tj ET\r\n"
	"BT /Symbol 11 Tf 471.5026 123.9289 Td (\\273) Tj ET\r\n"
	"BT /Symbol 11 Tf 485.6758 123.9289 Td (\\274) Tj ET\r\n"
	"BT /Symbol 11 Tf 499.8491 123.9289 Td (\\275) Tj ET\r\n"
	"BT /Symbol 11 Tf 514.0223 123.9289 Td (\\276) Tj ET\r\n"
	"BT /Symbol 11 Tf 528.1955 123.9289 Td (\\277) Tj ET\r\n"
	"BT /Symbol 11 Tf 315.5971 109.7557 Td (\\300) Tj ET\r\n"
	"BT /Symbol 11 Tf 329.7703 109.7557 Td (\\301) Tj ET\r\n"
	"BT /Symbol 11 Tf 343.9435 109.7557 Td (\\302) Tj ET\r\n"
	"BT /Symbol 11 Tf 358.1168 109.7557 Td (\\303) Tj ET\r\n"
	"BT /Symbol 11 Tf 372.29 109.7557 Td (\\304) Tj ET\r\n"
	"BT /Symbol 11 Tf 386.4632 109.7557 Td (\\305) Tj ET\r\n"
	"BT /Symbol 11 Tf 400.6364 109.7557 Td (\\306) Tj ET\r\n"
	"BT /Symbol 11 Tf 414.8097 109.7557 Td (\\307) Tj ET\r\n"
	"BT /Symbol 11 Tf 428.9829 109.7557 Td (\\310) Tj ET\r\n"
	"BT /Symbol 11 Tf 443.1561 109.7557 Td (\\311) Tj ET\r\n"
	"BT /Symbol 11 Tf 457.3294 109.7557 Td (\\312) Tj ET\r\n"
	"BT /Symbol 11 Tf 471.5026 109.7557 Td (\\313) Tj ET\r\n"
	"BT /Symbol 11 Tf 485.6758 109.7557 Td (\\314) Tj ET\r\n"
	"BT /Symbol 11 Tf 499.8491 109.7557 Td (\\315) Tj ET\r\n"
	"BT /Symbol 11 Tf 514.0223 109.7557 Td (\\316) Tj ET\r\n"
	"BT /Symbol 11 Tf 528.1955 109.7557 Td (\\317) Tj ET\r\n"
	"BT /Symbol 11 Tf 315.5971 95.5825 Td (\\320) Tj ET\r\n"
	"BT /Symbol 11 Tf 329.7703 95.5825 Td (\\321) Tj ET\r\n"
	"BT /Symbol 11 Tf 343.9435 95.5825 Td (\\322) Tj ET\r\n"
	"BT /Symbol 11 Tf 358.1168 95.5825 Td (\\323) Tj ET\r\n"
	"BT /Symbol 11 Tf 372.29 95.5825 Td (\\324) Tj ET\r\n"
	"BT /Symbol 11 Tf 386.4632 95.5825 Td (\\325) Tj ET\r\n"
	"BT /Symbol 11 Tf 400.6364 95.5825 Td (\\326) Tj ET\r\n"
	"BT /Symbol 11 Tf 415.0917 95.5825 Td (\\327) Tj ET\r\n"
	"BT /Symbol 11 Tf 428.9829 95.5825 Td (\\330) Tj ET\r\n"
	"BT /Symbol 11 Tf 443.1561 95.5825 Td (\\331) Tj ET\r\n"
	"BT /Symbol 11 Tf 457.3294 95.5825 Td (\\332) Tj ET\r\n"
	"BT /Symbol 11 Tf 471.5026 95.5825 Td (\\333) Tj ET\r\n"
	"BT /Symbol 11 Tf 485.6758 95.5825 Td (\\334) Tj ET\r\n"
	"BT /Symbol 11 Tf 499.8491 95.5825 Td (\\335) Tj ET\r\n"
	"BT /Symbol 11 Tf 514.0223 95.5825 Td (\\336) Tj ET\r\n"
	"BT /Symbol 11 Tf 528.1955 95.5825 Td (\\337) Tj ET\r\n"
	"BT /Symbol 11 Tf 315.5971 81.4092 Td (\\340) Tj ET\r\n"
	"BT /Symbol 11 Tf 329.7703 81.4092 Td (\\341) Tj ET\r\n"
	"BT /Symbol 11 Tf 343.9435 81.4092 Td (\\342) Tj ET\r\n"
	"BT /Symbol 11 Tf 358.1168 81.4092 Td (\\343) Tj ET\r\n"
	"BT /Symbol 11 Tf 372.29 81.4092 Td (\\344) Tj ET\r\n"
	"BT /Symbol 11 Tf 386.4632 81.4092 Td (\\345) Tj ET\r\n"
	"BT /Symbol 11 Tf 400.6364 81.4092 Td (\\346) Tj ET\r\n"
	"BT /Symbol 11 Tf 414.8097 81.4092 Td (\\347) Tj ET\r\n"
	"BT /Symbol 11 Tf 428.9829 81.4092 Td (\\350) Tj ET\r\n"
	"BT /Symbol 11 Tf 443.1561 81.4092 Td (\\351) Tj ET\r\n"
	"BT /Symbol 11 Tf 457.3294 81.4092 Td (\\352) Tj ET\r\n"
	"BT /Symbol 11 Tf 471.5026 81.4092 Td (\\353) Tj ET\r\n"
	"BT /Symbol 11 Tf 485.6758 81.4092 Td (\\354) Tj ET\r\n"
	"BT /Symbol 11 Tf 499.8491 81.4092 Td (\\355) Tj ET\r\n"
	"BT /Symbol 11 Tf 514.0223 81.4092 Td (\\356) Tj ET\r\n"
	"BT /Symbol 11 Tf 528.1955 81.4092 Td (\\357) Tj ET\r\n"
	"BT /Symbol 11 Tf 315.5971 67.236 Td (\\360) Tj ET\r\n"
	"BT /Symbol 11 Tf 329.7703 67.236 Td (\\361) Tj ET\r\n"
	"BT /Symbol 11 Tf 343.9435 67.236 Td (\\362) Tj ET\r\n"
	"BT /Symbol 11 Tf 358.1168 67.236 Td (\\363) Tj ET\r\n"
	"BT /Symbol 11 Tf 372.29 67.236 Td (\\364) Tj ET\r\n"
	"BT /Symbol 11 Tf 386.4632 67.236 Td (\\365) Tj ET\r\n"
	"BT /Symbol 11 Tf 400.6364 67.236 Td (\\366) Tj ET\r\n"
	"BT /Symbol 11 Tf 415.0917 67.236 Td (\\367) Tj ET\r\n"
	"BT /Symbol 11 Tf 428.9829 67.236 Td (\\370) Tj ET\r\n"
	"BT /Symbol 11 Tf 443.1561 67.236 Td (\\371) Tj ET\r\n"
	"BT /Symbol 11 Tf 457.3294 67.236 Td (\\372) Tj ET\r\n"
	"BT /Symbol 11 Tf 471.5026 67.236 Td (\\373) Tj ET\r\n"
	"BT /Symbol 11 Tf 485.6758 67.236 Td (\\374) Tj ET\r\n"
	"BT /Symbol 11 Tf 499.8491 67.236 Td (\\375) Tj ET\r\n"
	"BT /Symbol 11 Tf 514.0223 67.236 Td (\\376) Tj ET\r\n"
	"BT /Symbol 11 Tf 528.1955 67.236 Td (\\377) Tj ET\r\n"
	"0.1969 w 311.811 289.1339 m 311.811 62.3622 l 325.9843 289.1339 m 325.9843 62.3622 l 340.1575 289.1339 m 340.1575 62.3622 l 354.3307 289.1339 m 354.3307 62.3622 l 368.5039 289.1339 m 368.5039 62.3622 l 382.6772 289.1339 m 382.6772 62.3622 l 396.8504 289.1339 m 396.8504 62.3622 l 411.0236 289.1339 m 411.0236 62.3622 l 425.1969 289.1339 m 425.1969 62.3622 l 439.3701 289.1339 m 439.3701 62.3622 l 453.5433 289.1339 m 453.5433 62.3622 l 467.7166 289.1339 m 467.7166 62.3622 l 481.8898 289.1339 m 481.8898 62.3622 l 496.063 289.1339 m 496.063 62.3622 l 510.2362 289.1339 m 510.2362 62.3622 l 524.4095 289.1339 m 524.4095 62.3622 l 538.5827 289.1339 m 538.5827 62.3622 l 311.811 289.1339 m 538.5827 289.1339 l 311.811 274.9607 m 538.5827 274.9607 l 311.811 260.7875 m 538.5827 260.7875 l 311.811 246.6143 m 538.5827 246.6143 l 311.811 232.441 m 538.5827 232.441 l 311.811 218.2678 m 538.5827 218.2678 l 311.811 204.0945 m 538.5827 204.0945 l 311.811 189.9213 m 538.5827 189.9213 l 311.811 175.7481 m 538.5827 175.7481 l 311.811 161.5749 m 538.5827 161.5749 l 311.811 147.4016 m 538.5827 147.4016 l 311.811 133.2284 m 538.5827 133.2284 l 311.811 119.0552 m 538.5827 119.0552 l 311.811 104.882 m 538.5827 104.882 l 311.811 90.7087 m 538.5827 90.7087 l 311.811 76.5355 m 538.5827 76.5355 l 311.811 62.3622 m 538.5827 62.3622 l  S"
	"BT /Helvetica 10 Tf 56.6929 53.8583 Td (Schrift: Helvetica) Tj ET"
	"BT /Helvetica 10 Tf 311.811 53.8583 Td (Schrift: Symbol) Tj ET"
 "0 g BT /Helvetica 10 Tf 297.6378 34.0158 Td (1\\0577) Tj ET";

	uncompressed=(uint8*)test.ToCString();
	uncompressedLength=0;
	while(uncompressed[uncompressedLength]!=0)uncompressedLength++;

	std::cout << "Uncompressed Length: " << uncompressedLength << std::endl;

	//Komprimieren
	compressed=NULL;
	compressedLength=0;
	deflater.Reset();
	deflater.SetInput(uncompressed, uncompressedLength);
	deflater.Deflate(compressed, compressedLength);

	std::cout << "Compressed Length: " << compressedLength << std::endl;

	//Dekomprimieren
	restored=NULL;
	restoredLength=0;
	inflater.Reset();
	inflater.SetInput(compressed, compressedLength);
	inflater.Inflate(restored, restoredLength);

	std::cout << "Restored Length: " << restoredLength << std::endl;

	//Vergleiche uncompressed und restored...
	TestEquals((int64)uncompressedLength,(int64)restoredLength,"Länge der Daten unterschiedlich.");

	l=std::min(uncompressedLength,restoredLength);

	for(uint32 a=0;a<l;a++)
	{
		TestEquals(uncompressed[a],restored[a],"Datenfehler in Kompression / Dekompression.");
	}

	delete[] uncompressed;
	delete[] compressed;
	delete[] restored;

	//
	// Teste langen codeblock mit 0
	//

	uncompressed=new uint8[1000000];
	uncompressedLength=1000000;
	for(uint32 a=0;a<uncompressedLength;a++)uncompressed[a]=0;

	std::cout << "Uncompressed Length: " << uncompressedLength << std::endl;

	//Komprimieren
	compressed=NULL;
	compressedLength=0;
	deflater.Reset();
	deflater.SetInput(uncompressed, uncompressedLength);
	deflater.Deflate(compressed, compressedLength);

	std::cout << "Compressed Length: " << compressedLength << std::endl;

	//Dekomprimieren
	restored=NULL;
	restoredLength=0;
	inflater.Reset();
	inflater.SetInput(compressed, compressedLength);
	inflater.Inflate(restored, restoredLength);

	std::cout << "Restored Length: " << restoredLength << std::endl;

	//Vergleiche uncompressed und restored...
	TestEquals((int64)uncompressedLength,(int64)restoredLength,"Länge der Daten unterschiedlich.");

	l=std::min(uncompressedLength,restoredLength);

	for(uint32 a=0;a<l;a++)
	{
		TestEquals(uncompressed[a],restored[a],"Datenfehler in Kompression / Dekompression.");
	}

	delete[] uncompressed;
	delete[] compressed;
	delete[] restored;

}
