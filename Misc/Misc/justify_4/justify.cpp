#if 0
compile line:
/usr/intel/pkgs/gcc/4.6.2/bin/g++ -std=c++0x justify2.cc
#endif

#include <memory>
#include <functional>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <numeric>
#include <vector>

using namespace std;

enum Alignment {LEFT, CENTER, RIGHT};
char const SPACE = ' ';
char const * DELIMITERS = " \n\t";

ostream & operator << (ostream & o, vector<string> const & v)
{
  for_each(v.begin(), v.end(), [&o] (string const & s) -> void { o << s << "|\n"; });
  return o;
}

// breaks up cs into individual tokens, based on delimiters
vector<string> tokenize(char * cs, char  const * delimiters)
{
  vector<string> tokens;
  char * tok = strtok(cs, delimiters);
  while(tok){
    tokens.push_back(tok);
    tok = strtok(NULL, delimiters);  
  }
  return tokens;
}
  
//left aligning a single line
string leftAlign(vector<string> allWords)
{
    auto it = allWords.begin();
    string lineSoFar = *it++;
    for ( ; it != allWords.end(); it++) {
	lineSoFar += " " + *it;
    }
    return lineSoFar;
}

// justifies st left, returns as vector
// of individual lines, left justified, no \n at end
vector<string> justifyLeft__(string const & st, size_t num)
{
  string cs(st.begin(), st.end()); // make deep copy
  auto words = tokenize(const_cast<char *>(cs.c_str()), DELIMITERS); // tokenize with specified delimiters

  typedef std::pair<unsigned int, vector<string> > LineInfoType;
  typedef vector<LineInfoType> AccumType;  //this corresponds to the accumulator type [(Int, [String])] in Haskell
  AccumType acc = {LineInfoType(0, vector<string>())};

  AccumType listNumAndWords = std::accumulate(words.begin(), words.end(), acc, 
    [num] (AccumType lenWdSeq, string word) -> AccumType
    {
	auto lenWdLast = lenWdSeq.back();
	auto currLen = lenWdLast.first; 
	auto currWds = lenWdLast.second; 

	LineInfoType thisWs;

	auto ret = lenWdSeq;
	ret.pop_back();
	
	auto getNewCurrLength = [] (unsigned int cl, string word) -> unsigned int { return (cl == 0 ? word.length() : cl + 1 + word.length());};

	if (getNewCurrLength(currLen, word) <= num) {
	    thisWs.first = getNewCurrLength(currLen, word);
	    thisWs.second = currWds;
	    thisWs.second.push_back(word);
	    ret.push_back(thisWs);
	} else {
	    thisWs.first = word.length();
	    thisWs.second.push_back(word);
	    ret.push_back(lenWdLast);
	    ret.push_back(thisWs);
	}

	return ret;
    });
  vector<string> final;
  for (auto it = listNumAndWords.begin(); it != listNumAndWords.end(); it++) {
      final.push_back(leftAlign((*it).second));
  }
  return final;
}

// generic justify function
// returns the result in vector of strings, each line justified according to alignment
// no \n at end of lines
vector<string> justify(string const & st, size_t pageWidth, Alignment alignment)
{
  auto retval = justifyLeft__(st, pageWidth); 
  if(alignment != LEFT){
    for(auto & s : retval){
      size_t trailingSpaceCount = pageWidth - s.size();
      if(alignment == CENTER) { trailingSpaceCount /= 2; }
      s.insert(0, trailingSpaceCount, SPACE); // prepend appropriate count of spaces for right or center justify
    }
  }
  return retval;
}
    
int main(void)
{
  string s("  I've been singing with my band, cross\t\t\n the wire cross \nthe land, I've seen every blue eyed floozy on the way, but their beauty and their style went kind of moot after a while, \ntake me to them dirty ladies every time,\tFat\tbottomed\tgirls\tyou\tmake\tthe\trocking world\tgo\tround.   ");

  cout << justify(s, 22, LEFT) << endl;
  cout << justify(s, 22, RIGHT) << endl;
  cout << justify(s, 22, CENTER) << endl;

  cout << justify(s, 13, LEFT) << endl;
  cout << justify(s, 13, RIGHT) << endl;
  cout << justify(s, 13, CENTER) << endl;
  return 0;
}

