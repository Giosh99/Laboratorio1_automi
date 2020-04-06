#include<iostream>
#include<map>
#include<vector>
#include "automata.h"
using namespace std;
typedef std::pair<int,char> tpair;

 //ridefinizione == per oggetti di tipo pair
 bool operator== (const pair<int*,char>& lhs, const pair<int*,char>& rhs)
{ return lhs.first==rhs.first && lhs.second==rhs.second; }

void AbstractDFA::initializeVector(int n) {
	for(int i =0; i<n;i++) {
		states->push_back(i);
	}
}
void AbstractDFA::defineSinkState(int i) {
	sink = &((*states)[i]);
}
void AbstractDFA::defineInitialeState(int i) {
	start = &((*states)[i]);
}
void AbstractDFA::defineFinalState(int i) {
	final = &((*states)[i]);
}
	void AbstractDFA::defineTransaction(int* source, char c, int* destination) {
		tr->insert(make_pair(make_pair(source, c),destination));
	}

	AbstractDFA::AbstractDFA(int noStates): states(new vector<int>()), tr(new map<pair<int*, char>, int*>()){
		initializeVector(noStates);
		start = &(*states)[0];
		final = &(*states)[noStates-2];
		sink = &(*states)[noStates-1];
		current = start;
	};
	AbstractDFA::~AbstractDFA() {
		states->clear();
		tr->clear();

	}

	void AbstractDFA::reset() {
		current = start;
	}

	void AbstractDFA::doStep(char letter) {
        bool found = false;
        for(map<pair<int*, char>, int*>::iterator it=tr->begin(); it!=tr->end(); ++it) {
            if(it->first == pair<int*,char>(current, letter)) {
                current = it->second;
                found = true;
            }
        }
		if(!found)
			current = sink;
    }
	bool AbstractDFA::isAccepting() {
		if(current==final) 
			return true;
		else return false;
	}
bool AbstractDFA::run(const string &inputWord) {
    this->reset();
    for(int i = 0; i < inputWord.length(); i++) {
        doStep(inputWord[i]);
    }
    return isAccepting();
}
	
 WordDFA::WordDFA(const string &word): AbstractDFA(word.length() +2){
	 for(int i =0;i<word.length();i++) {
		 tr->insert({pair<int*, char>(&(*states)[i],word[i]), &(*states)[i+1]});
	 }
 }
CommentDFA::CommentDFA():AbstractDFA(8), ok(false), ascii(127){ //6  per commento inline e 3 per commento multiline
	defineTransaction(start,'/',&(*states)[1]);		//da q0 a q1
	for(int i = 0; i<ascii; i++) {				//sink state da q0
		if(i!=47)
			defineTransaction(&(*states)[0],(char)i,sink);
	}
	
	for(int i = 0; i<ascii; i++) {				//sink state da q1
		if(i!=42 && i!=47)
			defineTransaction(&(*states)[1],i,sink);
	}
	
	
	defineTransaction(&(*states)[1],'/',&(*states)[2]);	//da q1 a q2
	
	for(int i = 0; i<ascii; i++) {				//self-loop su q2
		if(i!=10)
			defineTransaction(&(*states)[2],i,&(*states)[2]);
	}
	
	defineTransaction(&(*states)[2],10,&(*states)[6]);	//da q2 a q3
	///////////////////////////////////////////// commento inline fine/////////////////////////////////
///////////////////////////////// inizio commento multiline ////////////////////////////////	
	
	defineTransaction(&(*states)[1],42,&(*states)[4]);	//da q1 a q4
	
	for(int i = 0; i<ascii; i++) {				//self-loop su q4
		if(i!=42)
			defineTransaction(&(*states)[4],i,&(*states)[4]);
	}
	
	defineTransaction(&(*states)[4],'*',&(*states)[5]);	//da q4 a q5
	defineTransaction(&(*states)[5],'*',&(*states)[5]);	//self-loop su q5
	
	for(int i = 0; i<ascii; i++) {				//da q5 a q4
		if(i!=47)
			defineTransaction(&(*states)[5],i,&(*states)[4]);
	}
	defineTransaction(&(*states)[5],'/',&(*states)[6]);	//da q5 a q6
	
	for(int i = 0; i<ascii; i++) {				//sink state da q6
			defineTransaction(&(*states)[6],i,sink);
	}
	for(int i = 0; i<ascii; i++) {				//self-loop su sink state
			defineTransaction(sink,i,sink);
	}
}
     void CommentDFA::doStep(char letter) { // 
		bool ok = false;
        for(map<pair<int*, char>, int*>::iterator it=tr->begin(); it!=tr->end()&&!ok; it++) {
            if(it->first == pair<int*,char>(current, letter)) {
				ok = true;
                current = it->second;
            }
        }
	}