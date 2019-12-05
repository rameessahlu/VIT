// MeltAndMint.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>
#include "generateValue.h"
namespace str_fn
{
	template < typename T > std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
}

/*----------------------------------------------MINT-----------------------------------------------------------------------------------------*/
class Mint
{
	private:
	int int_number, modulus;
	public:
		Mint() {}
		Mint(int int_number) {
			this->int_number = int_number;
		}
		int operator -(Mint mint) {
			//int result = ((this->int_number - mint.get()) % this->modulus);
			//result = (result < 0) ? this->modulus + result : result;
			//return result;
			return (((this->int_number - mint.get()) % this->modulus) + this->modulus) % this->modulus;
		}
		int get() {
			return this->int_number;
		}

		void setModulus(int modulus) {
			this->modulus = modulus;
		}

		int getModulus() {
			return this->modulus;
		}
};


/*----------------------------------------------MELT-----------------------------------------------------------------------------------------*/

class Melt
{
	public:
		char english_alphabet;
		int modulus;
		Melt() {}
		Melt(char english_alphabet) {
			this->english_alphabet = english_alphabet;
			this->modulus = 26;
		};

		int operator -(Melt melt) {
			if (this->english_alphabet == melt.english_alphabet)
			{
				return 0;
			}
			else
			{
				return 1;
			}
		}

		char get() {
			return this->english_alphabet;
		}

		int getModulus() {
			return this->modulus;
		}
};
/*----------------------------------------------CODEBOOK-----------------------------------------------------------------------------------------*/

template <class T>
class Codebook
{
private:
public:
	int codeBookSize;
	int distanceMatrixSize;
	T *pType;
	int *Distances;

	//Constructors
	Codebook(int size = 2)
	{
		codeBookSize = size;
		distanceMatrixSize = (size*(size));
		pType = new T[size];
		Distances = new int[distanceMatrixSize];

		for (int i = 0; i < size; i++)
		{
			pType[i] = 0;
		}
		for (int i = 0; i < distanceMatrixSize; i++)
		{
			Distances[i] = 0;
		}
	}
	void reinitialization(int size)
	{
		codeBookSize = size;
		distanceMatrixSize = (size*(size));
		pType = new T[size];
		Distances = new int[distanceMatrixSize];

		for (int i = 0; i < size; i++)
		{
			pType[i] = 0;
		}
		for (int i = 0; i < distanceMatrixSize; i++)
		{
			Distances[i] = 0;
		}
	}
	//Destructor
	~Codebook() {
		delete[] pType;
	}
	//Overloaded operator "=" for initialization
	Codebook & operator = (const Codebook & rhs)
	{
		if (this == &rhs) { return *this; }

		delete[] pType;
		codeBookSize = rhs.GetCodeBookSize();
		distanceMatrixSize = (codeBookSize * (codeBookSize));
		pType = new T[codeBookSize];
		Distances = new T[distanceMatrixSize];

		for (int i = 0; i < codeBookSize; i++)
		{
			pType[i] = rhs[i];
		}

		for (int i = 0; i < distanceMatrixSize; i++)
		{
			distanceMatrixSize[i] = 0;
		}

		return *this;
	}
	//Overloaded operator "[]"
	T& operator [](int offSet) {
		return pType[offSet];
	}
	const T& operator [](int offSet) const {
		return pType[offSet];
	}

	int GetCodeBookSize() const { return codeBookSize; }
	void SetCodeBookSize(const int x) { codeBookSize = x; }
	
	int minimumWeight(){
		int minimumWeightAcrossCodeWords = 999;
		for (int i = 0; i < codeBookSize; i++) {
			if (pType[i].Weight() < minimumWeightAcrossCodeWords  && pType[i].Weight() > 0)
				minimumWeightAcrossCodeWords = pType[i].Weight();
		}
		return minimumWeightAcrossCodeWords;
	}
	
	void calcDistance() {
		int index = 0;
		for (int i = 0; i < codeBookSize; i++) {
			for (int j = 0; j < codeBookSize; j++) {
					Distances[index] = pType[i].Distance(pType[j]);
					//std::cout << "DEBUG " << index <<": " << Distances[index] << " ;";
					index = index + 1;
			}
		}
	}
	int minimumDistance()
	{
		int minDistance = 999;
		for (int i = 0; i < distanceMatrixSize; i++) {
			//std::cout << "DEBUG " << i << ": " << Distances[i] << " ;";
			if (Distances[i] < minDistance and Distances[i] > 0)
			{	
				minDistance = Distances[i];
			}
		}
		return minDistance;
	}

	void Display() {
		//for (int i = 0; i < distanceSize; i++) {
		//	std::cout << "";//Distances[i] << " ;\n";
		//}
		std::cout << "Distances: \n";
		for (int i = 0; i < codeBookSize; i++)
		{
			std::cout << pType[i].Display() << " \n";
		}
		std::cout << "Distance Matrix: \n";
		calcDistance();
		int slice = 0;
		for (int i = 0; i < distanceMatrixSize; i++)
		{
				std::cout << Distances[i] << " ";
				slice += 1;
				if (slice == 4)
				{
					std::cout << "\n";
					slice = 0;
				}
		}
		std::cout << "Min Weight: " << str_fn::to_string(minimumWeight()) + "\n";
		std::cout << "Min Distance: " << minimumDistance();
	}
};


/*----------------------------------------------CODEWORD-----------------------------------------------------------------------------------------*/

template <class T>
class Codeword
{
	private:
	public:
		int codeWordSize;
		int symbolType;
		T *pType;

		//Constructors
		Codeword(int size = 7, int symbol_type = 0)
		{
			this->codeWordSize = size;
			this->symbolType = symbol_type;
			pType = new T[size];

			for (int i = 0; i < size; i++)
			{
				pType[i] = 0;
			}
		}
		void reinitialization(int size, int symbol_type)
		{
			this->codeWordSize = size;
			this->symbolType = symbol_type;
			pType = new T[this->codeWordSize];

			for (int i = 0; i < this->codeWordSize; i++)
			{
				pType[i] = 0;
			}
		}
		//Destructor
		~Codeword() {
			delete [] pType;
		}
		//Overloaded operator "=" for initialization
		Codeword & operator = (const Codeword & rhs)
		{
			if (this == & rhs) { return *this; }

			delete[] pType;
			codeWordSize = rhs.GetCodeWordSize();
			pType = new T[codeWordSize];

			for (int i = 0; i < codeWordSize; i++)
			{
				pType[i] = rhs[i];
			}

			return *this;
		}
		//Overloaded operator "[]"
		T& operator [](int offSet) {
			return pType[offSet];
		}
		const T& operator [](int offSet) const {
			return pType[offSet];
		}

		int GetCodeWordSize() const { return codeWordSize; }
		void SetCodeWordSize(const int x) { codeWordSize = x; }

		int Weight()
		{
			int weight = 0;
			//std::cout << "DEBUG"<<str_fn::to_string(codeWordSize) << "cws";
			for (int i = 0; i < codeWordSize; i++)
			{
				if (symbolType == 0)
				{
					if (pType[i].get() != 0)
					{
						weight = weight + 1;
					}
					//std::cout << pType[i].get();
					//std::cout << "DEBUG:" << std::to_string(typeid(pType[i]) == typeid(Mint));
				}
				else
				{
					std::string temp(1, pType[i].get());
					if (temp != "a")
					{
						weight = weight + 1;
					}
				}
			}
			return weight;
		}
		std::string Display()
		{
			std::string output = "";
				
			for (int i = 0; i < codeWordSize; i++) {

				if (symbolType == 0)
				{
					output = output + str_fn::to_string(pType[i].get()) + " ";
				}
				else
				{
					std::string temp(1, pType[i].get());
					output = output + temp + " ";
				}
			}
			//std::cout << "cool" << output + "   " + std::to_string(Weight());
			return output + "   Weight: " + str_fn::to_string(Weight());
		}
		int Distance(Codeword & scw)
		{
			int total_diff = 0;
			for (int i = 0; i < codeWordSize; i++)
			{
				if (symbolType == 0)
				{
					Mint mint1(pType[i].get());
					mint1.setModulus(pType[i].getModulus());
					Mint mint2(scw[i].get());
					mint2.setModulus(scw[i].getModulus());
					
					int _diff = mint1 - mint2;

					//Mint m2(_diff);
					//m2.setModulus(pType[i].getModulus());
					//-m2;
					//std::cout << std::to_string(_diff) << " DEBUG:    " << std::to_string(m2.get()) << "\n";

					total_diff = total_diff + _diff;//m2.get();
				}
				else
				{
					Melt melt1(pType[i].get());
					Melt melt2(scw[i].get());

					int distance = melt1 - melt2;

					total_diff = total_diff + distance;

				}
			}
			return abs(total_diff);
		}
};

void CFC0(int symbolType, int seed, int length, int size, int modulus)
{
	Codebook<Codeword<Mint> > codebook;
	codebook.reinitialization(size);

	//Adding codewords to the codebook
	for (int j = 1; j < size; j++)
	{
		//codeword generation
		Codeword<Mint> cw;
		codebook.pType[j] = cw;
		codebook.pType[j].reinitialization(length, symbolType);

		for (int l = 0; l < length; l++)
		{
				Mint mint(generateMint(seed, modulus));
				mint.setModulus(modulus);
				codebook.pType[j].pType[l] = mint;
		}
	}

	Codeword<Mint> cw;
	codebook.pType[0] = cw;
	codebook.pType[0].reinitialization(length, symbolType);

	//Adding zero codeword
	for (int j = 0; j < length; j++)
	{
		Mint mint(0);
		codebook.pType[0].pType[j] = mint;
	}


	//std::cout << "Min Weight: " << std::to_string(codebook.minimumWeight()) + "\n";
	//codebook.calcDistance();
	//std::cout << "Min Distance: " << codebook.minimumDistance() << "\n";
	codebook.Display();
}

void CFC1(int symbolType, int seed, int length, int size)
{
	Codebook<Codeword<Melt> > codebook;
	codebook.reinitialization(size);


	Codeword<Melt> cw;
	codebook.pType[0] = cw;
	codebook.pType[0].reinitialization(length, symbolType);
	//Adding zero codeword
	for (int j = 0; j < length; j++)
	{
		Melt melt('a');
		codebook.pType[0].pType[j] = melt;
	}


	//Adding codewords to the codebook
	for (int k = 1; k < size; k++)
	{
		//codewords generation
		Codeword<Melt> cw;

		codebook.pType[k] = cw;
		codebook.pType[k].reinitialization(length, symbolType);

		for (int j = 0; j < length; j++)
		{
			Melt melt(generateMelt(seed));
			codebook.pType[k].pType[j] = melt;
		}
	}

	//std::cout << codebook.minimumWeight();
	codebook.Display();
}


/*----------------------------------------------MAIN-----------------------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
		int symbolType = atoi(argv[1]);
		int seed = atoi(argv[2]);
		int length = atoi(argv[3]);
		int size = atoi(argv[4]);

		if (symbolType == 0) //Mint
		{
			int modulus = atoi(argv[5]);
			CFC0(symbolType, seed, length, size, modulus);
		}
		else //Melt
		{
			CFC1(symbolType, seed, length, size);
		}
}
