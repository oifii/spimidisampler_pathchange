/*
 * Copyright (c) 2010-2016 Stephane Poirier
 *
 * stephane.poirier@oifii.org
 *
 * Stephane Poirier
 * 3532 rue Ste-Famille, #3
 * Montreal, QC, H2X 2L1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include <string>
#include <fstream>
#include <vector>

#include <iostream>
#include <sstream>
using namespace std;
//#include <stdlib.h>

#include <ctime>
#include <windows.h>

int main(int argc, char *argv[])
{
	///////////////////
	//read in arguments
	///////////////////
	char pathname_inputwavfolderfiles[2048] = {"D:\\oifii-org\\httpdocs\\ns-org\\nsd\\ar\\cp\\audio_spi\\spimidisampler"}; 
	//char pathname_nisamplelibrariesfolderlocation[2048] = {"C:\\Program Files (x86)\\Native Instruments"};
	//char pathname_nisamplelibrariesfolderlocation[2048] = {"E:"};
	char pathname_nisamplelibrariesfolderlocation[2048] = {"D:\\Program Files\\Native Instruments"};
	char pathname_outputwavfolderfiles[2048] = {"."};
	if(argc>1)
	{
		strcpy(pathname_inputwavfolderfiles, argv[1]);
	}
	if(argc>2)
	{
		strcpy(pathname_nisamplelibrariesfolderlocation, argv[2]);
	}
	if(argc>3)
	{
		strcpy(pathname_outputwavfolderfiles, argv[3]);
	}

	///////////////////////////////////////////////////////
	//execute cmd line to get all wavfolder_*.txt filenames
	///////////////////////////////////////////////////////
	string path = pathname_inputwavfolderfiles;
	string path2 = pathname_outputwavfolderfiles;
	string path3 = pathname_nisamplelibrariesfolderlocation;
	//string cmdline = "DIR " + path + "\\" + "wavfolder_*.txt /B /O:N > txtfilenames.txt";
	string cmdline = "DIR " + path + "\\" + "wavfolder*.txt /B /O:N > txtfilenames.txt";
	system(cmdline.c_str());


	///////////////////////////////////////
	//load filenames.txt into string vector
	///////////////////////////////////////
	vector<string> txtfilenames;
	ifstream ifs("txtfilenames.txt");
	string temp;
	while(getline(ifs,temp))
	{
		//temp = path + "\\" + temp;
		txtfilenames.push_back(temp);
	}

	vector<string>::iterator it;	
	for ( it=txtfilenames.begin() ; it < txtfilenames.end(); it++ )
	{
		vector<string> wavfilenames;
		temp = path + "\\" + *it;
		//ifstream ifs(*it); //*it is a wavfolder_*.txt filename
		ifstream ifs;
		ifs.open(temp);
		string temp;
		while(getline(ifs,temp))
		{
			wavfilenames.push_back(temp);
		}
		temp = path2 + "\\" + *it;
		ofstream ofs;
		ofs.open(temp);
		
		//////////////////////////////////////////////////
		//browse throught wav filenames and write new path
		//////////////////////////////////////////////////
		string quote;
		quote = "\"";
		string cmdbuffer;

		vector<string>::iterator iterator;	
		for ( iterator=wavfilenames.begin() ; iterator < wavfilenames.end(); iterator++ )
		{
			std::size_t foundpos = (*iterator).find("Sample Libraries");
			if(foundpos!=std::string::npos)
			{
				temp = path3 + "\\" + (*iterator).substr(foundpos);
				ofs << temp << endl;
			}
			else
			{
				ofs << *iterator << endl; //*it is a .wav filename
			}
			//cout << *iterator << endl; //*it is a .wav filename
			/*
			if((*iterator).rfind(".txt")==string::npos)
			{
				
				system("del spd_ok.txt");
				
				cout << *iterator << endl; //*it is a .wav filename
				
				cmdbuffer = "spipitchdetection.exe " + quote + *iterator + quote + " " + maxdetectionduration;
				cout << cmdbuffer << endl;
				system(cmdbuffer.c_str());
				bool found = false;
				do
				{
					FILE* pFILE = fopen("spd_ok.txt", "r");
					if(pFILE)
					{
						found=true;
						fclose(pFILE);
					}
					else
					{
						Sleep(500);
					}
				} while(!found);
				
			}
			*/
		}
		ifs.close();
		ofs.close();
	}
	return 0;
}