#include <stdlib.h>
#include <stdio.h>
#include <cv.h>
#include <highgui.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <highgui.h>
#include <string.h>
#include <stdint.h>
#include <vector>
#include <list>

#include <string> 

using namespace cv;
using namespace std;
//Functions Area
void printTree(int w, int p, int l, int r, char alp);
void findLow(vector<int>& weight, vector<int>& parent,int &locf,int &locs,int &second,int &first);
void addRow(vector<int>& weight, vector<int>& parent, vector<int>& left, vector<int>& right, vector<char>& alpha, int &first, int &second, int &p1, int &p2, int &sum, int &locf, int &locs);
bool parentTest(vector<int>& parent);


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//nish start
bool leafTest(vector<int>& leftleaf,vector<int>& rightleaf, int &loc_child)     	;
void findBigParent(vector<int>& weight,vector<int>& parent,vector<int>& left,vector<int>& right,int tree_weight, int &left_match,int &right_match,vector<char>& bits_rep, int sp_find, int bp_find)	;

//nish end
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//Main
int main( int argc, char** argv )
{
char a[] = "huffman is the best compression algorithm";
int count, repeat = 0;
int * converter;
int temp; 
char ctemp;
printf("\n\nThis is input string: %s \n",a);
//part 1, sorts input string to number of occurences
int string_size = sizeof(a)/sizeof(char)-1; // -1 removes termination character from char
printf("string contains: %d elements\n", string_size);
	
//lets make a vector containing the letters
std::vector<char> vec;		//vector holds the unique char
std::vector<int> val;		//val holds the # of reoccurences
std::vector<int> weight;
std::vector<int> parent;
std::vector<int> left;
std::vector<int> right;
std::vector<char> alpha;
//===========================================================================
//Add the string into the vector if non-repeating char=======================

vec.push_back(a[0]);	//Initial vec value

std::cout << "\n\nThe unique vector size is:" << vec.size() << "\n \n";
for(int i=1;i<string_size;i++)
{
	for(int j=i-1;j>-1;j--)
	{			
		if(a[i] == vec[j])
		{
		count++;	
		}
	}
	if (count == 0)
	{
	vec.push_back(a[i]);
	}
	else
	{
	count = 0;
	}
	
}


int vecsize = vec.size();	//get char vec vector size
std::cout << "\n\nThe unique vector size second time is:" << vec.size() << "\n \n";
std::cout << "\n Vec 1" << vec.at(1) << "\n \n";
//===========================================================================
//Count  # of char repetitions and store @ same index as vec in val

for(int i=0; i<vecsize; i++)
{
	for(int j=0; j<string_size; j++)
	{
		if (vec[i] == a[j])
		{
		repeat++;
		}	
	}
val.push_back(repeat);
repeat=0;
}

int valsize = val.size();       // get int weights vector size
// DISPLAY CURRENT STATE
std::cout << "____________Here is the vector \n";

for(int n =0; n<vecsize; n++)
{
ctemp = vec.at(n);
std::cout << ctemp << "";
}
std::cout << '\n';
for(int n =0; n<vecsize; n++)
{
temp = val.at(n);
std::cout << temp << "";
}
std::cout << "\n\n____________Here is the repetition count:";
std::cout << '\n';
//============================================================================
//Sort the vectors
int a1, b1, c1, d1, e1, f1 =0;

for (int i=1; i<valsize; i++)
{
	for (int j=0; j<valsize; j++)
	{
		int jval = val.at(j);
		int ival = val.at(i);
		if (jval>ival)
		{
		usleep(10);
		a1 = val.at(i);
		b1 = val.at(j);
		c1 = vec.at(i);
		d1 = vec.at(j);
		usleep(10);
		val.at(i)=b1;
		val.at(j)=a1;
		vec.at(i)=d1;
		vec.at(j)=c1;
		usleep(10);		
		}	

	}
}

// At this point Val has been sorted
// Print reorganized chars and vals here
valsize = val.size();
vecsize = vec.size();
usleep(1000);

for(int n=0; n<valsize; n++)
{
temp = val.at(n);				// temp variable needed due to 
std::cout << temp << " ";			//cout data curroption when 2 
}						//print loops are needed	
std::cout << '\n';
usleep(1000);

for(int m=0; m<vecsize; m++)
{
ctemp = vec.at(m);
std::cout << ctemp << " ";
}
usleep(1000);

std::cout << '\n';
std::cout << "Val size is " << valsize << " " <<'\n';

//============================================================================
//------------- BINARY TREE

int w, p, l, r;
int first, second, sum, p1, p2;
int locs, locf;
char alp;
int treeout;
bool isparent;
int weightsize;
//Initialize tree
for (int n=0; n<valsize; n++)
{
 int aa = val.at(n);
 weight.push_back(aa);
 int bb = vec.at(n);
 alpha.push_back(bb);	
 parent.push_back(-1);
 left.push_back(-1);
 right.push_back(-1); 

w = weight.at(n);
p = parent.at(n);
l = left.at(n);
r = right.at(n);
alp = alpha.at(n);

printTree(w,p,l,r,alp);
} 

	// Part 0 - Create pairs of lowest values
	first = weight.at(0);	//Initialize the lowest weight value as start
	second = weight.at(1);
	locf = 0;		//set location of first to first value
	locs = 1;
	//Find the lowest two values using this function
//	parent.at(0) = 18;
//	parent.at(1) = 18;



	// Test to see if we have reached the end condition of the tree aka only 1 parent
	// with -1 in its value
while (parentTest(parent)==false)
{

	findLow(weight, parent, locf, locs, second, first);		//<-----------1
	
	//At the end of this loop we have the 2 lowest value
	// We have the loc of f and s

	std::cout << "locf is " << locf << " " <<'\n';
	std::cout << "locs is " << locs << " " <<'\n';

	// We add a new row and fill new parents
	addRow(weight,parent,left,right,alpha,first,second,p1,p2,sum,locf,locs);//<----2
 	first = 9999;	// reset first and second
	second = 9998;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/// the line below, printing of sum , parent 0 and 1
/// this command is whats causing the tree to remove the 'U' alphabet
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//	std::cout << "sum is:" << sum << "  parent of 0 and 1: " << p1 << " " << p2 <<'\n';
	//Print tree again
	
	weightsize = weight.size();
	std::cout << "weight size is: " << weightsize <<'\n';


//	for (int n=0; n<weightsize; n++)
//	{
//		std::cout << n << ". ";
//		w = weight.at(n);
//		p = parent.at(n);
//		l = left.at(n);
//		r = right.at(n);
//		alp = alpha.at(n);
//		printTree(w,p,l,r,alp);
//	} 

}	// END OF PARENT TEST	



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//nish start
char dictionary[valsize][5];//18symbols 26alphabets and 2^5=32 so 5 bits needed minimum
char dict_alpha[valsize];//stores the symbol alphabets

int tree_size, tree_weight;
int loc_child=0, bp_find=0, sp_find=0;
int left_match=0, right_match=0;
std::vector<char> bits_rep;

while (leafTest(left,right, loc_child)==true)
{		
	sp_find = loc_child;
	bp_find = parent.at(loc_child);
	left_match  = left.at(loc_child);
	right_match = right.at(loc_child);
	printf("\n");

	tree_size = weight.size();		//size of tree is 35
	tree_weight = weight.at(tree_size-1);	//weight of (index: 35) is 41,

	//go to the recursive function			
	findBigParent(weight,parent,left,right, tree_weight, left_match, right_match, bits_rep, sp_find, bp_find);
	
	char  x;
	int  x_size= bits_rep.size();


	int bits_column = 0;

	if (bits_column < x_size)
	{
	bits_column= x_size;
	}

	///prints out the decoded bits of each alpha
	///at the same time stores each alpha bits into the dictionary
		for(int i=0; i < x_size; i++)
		{
		 x= bits_rep.at(i);
		dictionary[loc_child][i]= bits_rep.at(i);
		 cout << " " << x << " ";
		}
//####################################################################################
//nish start

	dict_alpha[loc_child] =alpha.at(loc_child);

		for(int j=0; j < 5; j++)
		{
			 if( (!(dictionary[loc_child][j]== '0')&&!(dictionary[loc_child][j]== '1')) )
			{
			 dictionary[loc_child][j] ='9' ;
			}
		}
	
cout << "	index: " << loc_child <<  "	alpha: " << dict_alpha[loc_child];
bits_rep.clear();

}	//while loop end brace

	//prints out the stored dictonary bits and symbol
	for(int i=0; i < valsize; i++)
	{
	printf("\n%c:", dict_alpha[i]);
			for(int j=0; j < 5; j++)
				{
				 cout << " " <<  dictionary[i][j] << " ";
				}
	}

printf("\n");


//runs the "huffman is the best compression algorithm" sentences 
//and prints outs the respective bits representation for each letter	
for(int i=0	;i<string_size;i++)
{
	for(int j=0;j< valsize;j++)
	{			
		if(a[i] == dict_alpha[j])
		{
		cout << "" <<  dict_alpha[j] << " :";
			for(int k=0;k< 5;k++ )
			{
					if(! (dictionary[j][k] =='9') )
					{		
					cout <<  dictionary[j][k];
					}
			}		
		}	
	}
printf("\n");
}

bits_rep.clear();

//nish end
//####################################################################################

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Finaly print of binary tree
printf("\n The final binary tree \n");
	for (int n=0; n<weightsize; n++)
	{
		std::cout << n << ". ";
		w = weight.at(n);
		p = parent.at(n);
		l = left.at(n);
		r = right.at(n);
		alp = alpha.at(n);
		printTree(w,p,l,r,alp);
	}





val.clear();vec.clear();
weight.clear();
parent.clear();
left.clear();
right.clear();
alpha.clear();
return(0);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//nish start

	//this recursive function findBigParent will try to find the left or right leaf/child 
	//and compares with small parent index and pushes either a: 0 or 1 
void findBigParent(vector<int>& weight,vector<int>& parent,vector<int>& left,vector<int>& right,int tree_weight, int &left_match,int &right_match,vector<char>& bits_rep, int sp_find, int bp_find)
{	
	int tree_w = weight.at(bp_find);
	
	left_match = left.at(bp_find);
	right_match = right.at(bp_find);

	if(tree_w < tree_weight)
	{
			if(left_match == sp_find)
			{
			 //printf("0:");
			 bits_rep.push_back('0');
			}	
			else if(right_match == sp_find)
			{
			 //printf("1:");
			 bits_rep.push_back('1');
			}	
	bp_find = parent.at(bp_find);
	sp_find = parent.at(sp_find);
					
	findBigParent(weight,parent,left,right, tree_weight, left_match, right_match, bits_rep, sp_find, bp_find);
	}

	if( tree_w == tree_weight)
	{
			if(left_match == sp_find)
			{
			//printf("0:");
			bits_rep.push_back('0');
			}
			else if(right_match == sp_find)
			{
			//printf("1:");
			bits_rep.push_back('1');
			}
	}
}

	// this function goes through the tree to see which index is an alphabet,
	// by looking at its children left and right that has a : -1
	// once it finds an alphabet it will break the program and returns: false
bool leafTest(vector<int>& leftleaf,vector<int>& rightleaf, int &loc_child)
{
	int leaf_count =0;
        int l_val =0, r_val=0;
        int tree_size = 0;

	tree_size = leftleaf.size();
	for (int i=0; i<tree_size; i++)
	{
	 r_val = rightleaf.at(i);
	 l_val = leftleaf.at(i);
		if(l_val == -1 && r_val == -1)
		{
	 	 loc_child = i;
		 leaf_count++;
		 leftleaf.at(i) = 0 ;	//once you discover a child set its right and left to zero
		 rightleaf.at(i) = 0 ;   //so you won't go back to same child in the loop second time around 
		
		 break; //if child is discover break out of loop
		}
	}
		if (leaf_count>1)
		{
		 return (false); 
		}
		else if (leaf_count==1)
		{
		 return(true);
		}
}

//nish end of functions: my implementation is done after this point / line
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void printTree(int w, int p, int l, int r, char alp)
{	
	std::cout << w << " " << p << " " << l << " " << r << " " << alp <<'\n';
}
void findLow(vector<int>& weight,vector<int>& parent,int &locf,int &locs,int &second,int &first)
{	
	int current, currentp;
	for (int x=0; x< weight.size(); x++)
	{ 
		current = weight.at(x);
		currentp = parent.at(x);
		//printf("\n %d is current p \n", currentp); 
		if (currentp == -1)
		{
			if (current < first)
			{			 
			 locf = x;		//update value of first
			 first = current;			 	 
			} 						
			else if ((current <second) && (current >= first))
			{
			 locs = x;
			 second = current;	//update value of second
			}
		}
	}
}
void addRow(vector<int>& weight, vector<int>& parent, vector<int>& left, vector<int>& right, vector<char>& alpha, int &first, int &second, int &p1, int &p2, int &sum, int &locf, int &locs)
{
	sum = first + second;

	weight.push_back(sum);			//Set weight of new row
	parent.push_back(-1);			//Initialize parent of new row
	left.push_back(locf);			//Set left child 
	right.push_back(locs);			//Set right child
	alpha.push_back(0);			//Initialize alaphabet of parent as 0 for reference
	int weightmarker = weight.size()-1;

	//Set new parent values to original vals
	p1 = p2 = weightmarker;
	parent.at(locf) = weightmarker;
	parent.at(locs) = weightmarker;

}
bool parentTest(vector<int>& parent)
{
	int pcount =0;
        int pval =0;
        int psize = 0;
	psize = parent.size();
	for (int i=0; i<psize; i++)
	{
		pval = parent.at(i);
		if(pval == -1)
		{
		pcount++;
		//cout<< "\n "<< pcount << ": P count value \n";
		}
	}
	if (pcount > 1)
	{
	return(false);
	}
	else if(pcount == 1);
	{
	return(true);
	}	
}



	
