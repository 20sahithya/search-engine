#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include "student.h"

using namespace std;

void student::calculate()
{
	per=(sub1+sub2+sub3+sub4+sub5)/5.0;
	if(per>=90)
		grade='A+';
	else if(per>=80)
		grade='A';
	else if(per>=75)
		grade='A-';
	else if(per>=70)
		grade='B+';
	else if(per>=65)
		grade='B';
	else if(per>=60)
		grade='B-';
	else if(per>=55)
		grade='C+';
	else if(per>=50)
		grade='C';
	else
		grade='F';
}

void student::getdata()
{
	cout<<"\nEnter The adm number of the student ";
	cin>>admnum;
	cout<<"\n\nEnter student's Name: ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter student's subject 1 marks: ";
	cin>>sub1;
	cout<<"\nEnter student's subject 2 marks: ";
	cin>>sub2;
	cout<<"\nEnter student's subject 3  marks: ";
	cin>>sub3;
	cout<<"\nEnter student's subject 4 marks: ";
	cin>>sub4;
	cout<<"\nEnter student's subject 5 marks : ";
	cin>>sub5;
	calculate();
}

void student::showdata()
{
	cout<<"\nAdmission_Number: "<<admnum;
	cout<<"\nName: "<<name;
	cout<<"\nsubject 1 marks: "<<sub1;
	cout<<"\nsubject 2 marks: "<<sub2;
	cout<<"\nsubject  3 marks: "<<sub3;
	cout<<"\nsubject 4 marks: "<<sub4;
	cout<<"\nsubject 5 marks: "<<sub5;
	cout<<"\nPercentage: "<<per;
	cout<<"\nLetter Grade: "<<grade;
}

void write_student()
{
	student s;
	ofstream outFile;
	outFile.open("Students.dat",ios::binary|ios::app);
	s.getdata();
	outFile.write(reinterpret_cast<char *> (&s), sizeof(student));
	outFile.close();
    	cout<<"\n\nStudent record Has Been Created ";
	cin.ignore();
	cin.get();
}
void addData()
{
 ofstream fout;
 fout.open("Students.dat",ios::binary|ios::out|ios::app);
 s.getdata();
 fout.write((char*)&s,sizeof(s));
 fout.close();
 cout<<"\n\nData Successfully Saved to File....\n";
}


void displayData()
{
 ifstream fin;
 fin.open("Students.dat",ios::in|ios::binary);
 while(fin.read((char*)&s,sizeof(s)))
 {
  s.showdata();
 }
 fin.close();
 cout<<"\n\nData Reading from File Successfully Done....\n";
}



class node
{
    public:
    student key;
    node *left, *right;
};


node* newNode(student key)
{
    node* Node = new node();
    Node->key = key;
    Node->left = Node->right = NULL;
    return (Node);
}

// A utility function to right
// rotate subtree rooted with y

node *rightRotate(node *x)
{
    node *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// A utility function to left
// rotate subtree rooted with x

node *leftRotate(node *x)
{
    node *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// This function brings the key at
// root if key is present in tree.
// If key is not present, then it
// brings the last accessed item at
// root. This function modifies the
// tree and returns the new root
node *splay(node *root,student key)
{
    // Base cases: root is NULL or
    // key is present at root
    if (root == NULL || root-> key.admnum == key.admnum &&
         root-> key.name == key.name &&
         root->key.gender==key.gender &&
          root-> key.per == key.per &&
           root-> key.grade == key.grade)
        return root;

    // Key lies in left subtree
    if (root->key.admnum > key.admnum || root-> key.admnum == key.admnum &&
        root-> key.name > key.name || root-> key.admnum == key.admnum && root->key.name ==key.name && root->key.grade > key.grade
        )
    {
        // Key is not in tree, we are done
        if (root->left == NULL) return root;

        // Zig-Zig (Left Left)
        if (root->left->key > key)
        {
            // First recursively bring the
            // key as root of left-left
            root->left->left = splay(root->left->left, key);

            // Do first rotation for root,
            // second rotation is done after else
            root = rightRotate(root);
        }
        else if (root->left->key < key) // Zig-Zag (Left Right)
        {
            // First recursively bring
            // the key as root of left-right
            root->left->right = splay(root->left->right, key);

            // Do first rotation for root->left
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }

        // Do second rotation for root
        return (root->left == NULL)? root: rightRotate(root);
    }
    else // Key lies in right subtree
    {
        // Key is not in tree, we are done
        if (root->right == NULL) return root;

        // Zig-Zag (Right Left)
        if (root->right->key > key)
        {
            // Bring the key as root of right-left
            root->right->left = splay(root->right->left, key);

            // Do first rotation for root->right
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        else if (root->right->key < key)// Zag-Zag (Right Right)
        {
            // Bring the key as root of
            // right-right and do first rotation
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }

        // Do second rotation for root
        return (root->right == NULL)? root: leftRotate(root);
    }
}

// Function to insert a new key k
// in splay tree with given root
node *insert(node *root, student k)
{
    // Simple Case: If tree is empty
    if (root == NULL) return newNode(k);

    // Bring the closest leaf node to root
    root = splay(root, k);

    // If key is already present, then return
    if (root->key == k) return root;

    // Otherwise allocate memory for new node
    node *newnode = newNode(k);

    // If root's key is greater, make
    // root as right child of newnode
    // and copy the left child of root to newnode
    if (root->key > k)
    {
        newnode->right = root;
        newnode->left = root->left;
        root->left = NULL;
    }

    // If root's key is smaller, make
    // root as left child of newnode
    // and copy the right child of root to newnode
    else
    {
        newnode->left = root;
        newnode->right = root->right;
        root->right = NULL;
    }

    return newnode; // newnode becomes new root
}

// A utility function to print
// preorder traversal of the tree.
// The function also prints height of every node
void preOrder(node *root)
{
    if (root != NULL)
    {
        cout<<root->key<<" ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

/* Driver code*/
int main()
{
    node *root = newNode(100);
    root->left = newNode(50);
    root->right = newNode(200);
    root->left->left = newNode(40);
    root->left->left->left = newNode(30);
    root->left->left->left->left = newNode(20);
    root = insert(root, 25);
    cout<<"Preorder traversal of the modified Splay tree is \n";
    preOrder(root);
    return 0;
}