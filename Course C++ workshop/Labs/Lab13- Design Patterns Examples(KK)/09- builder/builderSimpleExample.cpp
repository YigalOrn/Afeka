#include <iostream>
using namespace std;

#include "list"
#include "string"

class Document
{
public:
	void add(const string& part) {parts.push_back(part);}
	void show() const
	{
		cout << "\nThe document -------\n";
		list<string>::const_iterator itr = parts.begin();
		list<string>::const_iterator itrEnd = parts.end();
		for ( ; itr != itrEnd ; ++itr)
			cout << (*itr).c_str();
		cout << endl;
	}
private:
	list<string> parts;
}; // Product

class IBuilder
{
public:
	IBuilder() {theDocument = new Document;}
	virtual ~IBuilder() {delete theDocument;}

	virtual void buildTitle (const string& theTitle)   = 0;
	virtual void buildAuthor(const string& theAuthor)  = 0;

	Document* getResult() const {return theDocument;}

protected:
	Document* theDocument;
}; // IBuilder

class CV : public IBuilder
{
public :
	virtual void buildTitle (const string& theTitle)  {theDocument->add("CV\n");}	
	virtual void buildAuthor(const string& theAuthor) {theDocument->add("Name: " + theAuthor + "\n");}
}; // ConcreteBuilder1 : CV

class Article : public IBuilder
{
public :
	virtual void buildTitle (const string& theTitle)  {theDocument->add(theTitle + " / ");}	
	virtual void buildAuthor(const string& theAuthor) {theDocument->add(theAuthor);}
}; // ConcreteBuilder2 : Article

class Builder
{
public:
	void construct(IBuilder* builder, const string& theTitle, const string& theAuthor)
	{
		builder->buildTitle (theTitle);
		builder->buildAuthor(theAuthor);
	}
}; // Builder

void main()
{ 
	Builder builder;

	IBuilder* b1 = new CV();
	IBuilder* b2 = new Article();

	// Construct two products 
	builder.construct(b1, "CV", "Keren Kalif");
	Document* d1 = b1->getResult();
	d1->show();

	builder.construct(b2, "Independence Day for students: how to party chip", "Moran Regev");
	Document* d2 = b2->getResult();
	d2->show();

	delete d1;
	delete d2;
}

/*
Product Parts -------
PartA
PartB

Product Parts -------
PartX
PartY
*/