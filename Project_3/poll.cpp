#include <iostream>
#include <cassert>
#include <string>
#include <cctype>
using namespace std;

//given isValidUppercaseStateCode function
bool isValidUppercaseStateCode(string stateCode)
{
	const string codes =
		"AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.HI.ID.IL.IN.IA.KS."
		"KY.LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NJ.NH.NM.NY.NC."
		"ND.OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
	return (stateCode.size() == 2 &&
		stateCode.find('.') == string::npos &&  // no '.' in stateCode
		codes.find(stateCode) != string::npos);  // match found
}

bool hasRightSyntax(string pollData)
{	
	int start = 0;
	int end = pollData.size();
	while (start < end) {
		//get the first letter in the sequence and see if it is valid
		if (!isalpha(pollData.at(start))) {
			return false;
		}
		start +=1;

		//check if the next part of the string is a number or not
		if (start >= end || !isdigit(pollData.at(start))) {
			return false;
		}

		start+=1;

		//checks if double digit number and moves 'start' if it is. Does not return false because single digit numbers exist
		if (start < end && isdigit(pollData.at(start))) {
			start+=1;
		}

		//checking for the state code and make sure not out of scope
		if (start+1 >=end || !isalpha(pollData.at(start)) || !isalpha(pollData.at(start+1))) {
			return false;
		}
		//creates uppercase state code by combining two single-letter uppercase strings
		string stateCode = string(1, toupper(pollData.at(start))) + string(1, toupper(pollData.at(start+1)));

		//checks if the state code is valid
		if (!isValidUppercaseStateCode(stateCode)) {
			return false;
		}

		start += 2; 
	}

	
	return true;
}


	

int computeVotes(string pollData, char party, int& voteCount)
{
	// If the parameter pollData is not a poll data string this function returns 1.
	if (!hasRightSyntax(pollData)) {
		return 1;
	}
	
	//If the parameter party is not a letter, this function returns 3
	if (!isalpha(party)) {
		return 3; 
	}


	// if pollData is a poll data string in which at least one state prediction predicts zero electoral votes for that state, this function returns 2.
	int start = 0; 
	int end = pollData.size();
	while (start < end) {
		if (pollData.at(start) == '0') {
			if (pollData.at(start + 1) == '0' || (isalpha(pollData.at(start + 1)) && isalpha(pollData.at(start - 1)))) {
				return 2;
			}
		}
		start++;
	}
	
	
	start = 0;
	end = pollData.size();
	party = toupper(party);
	voteCount = 0;
	//tally up votes and update votecount 
	while (start < end) {
		if (toupper(pollData.at(start)) == party) {
			string addVote;
			
			while (isdigit(pollData.at(start+1))) {
				addVote += pollData.at(start+1);
				start++;

			}
			voteCount += stoi(addVote);
			start += 2; //account for state code
			
		}
		start++;
	}
	cerr << voteCount << " " << party;
	return 0;
}

int main()
{

	
	
	string test;
	int vote = 999;
	getline(cin, test);
	bool result = hasRightSyntax(test);
	cerr << "syntax " << result << endl;;
	int resultSecond = computeVotes(test, 'R', vote);
	
	cerr <<endl<< "computeVotes " << resultSecond << endl;
	
}