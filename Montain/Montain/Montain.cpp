#include <iostream>
#include <strstream>

using namespace std;

struct Section
{
	int heigth = 0;
	bool peak = false;
};

const int MAX_N = 10000;
const int MAX_PEAKS = 5000;
int neededPeakPositions[MAX_PEAKS];
Section montain[MAX_N];
int n = 0;
int peakCount = 0;

string stringJoin(int* array, unsigned int arrayLength, string separator = " ")
{
	strstream result;
	result << "";
	if (arrayLength != 0)
	{
		result << array[0];
		for (int i = 1; i < arrayLength; ++i)
		{
			result << separator << array[i];
		}
	}
	result << '\0';
	string resultStr = result.str();
	return resultStr;
}

int setToNextPeakIndex(int* pointer)
{

	int i = *pointer + 1;
	while (i < n && !montain[i].peak)
	{
		++i;
	}
	if (i == n)
	{
		*pointer = -1;
	}
	else
	{
		*pointer = i;
	}
	return *pointer;
}

int main()
{
	int neededNeighbours = 0;
	cin >> n >> neededNeighbours;
	for (int i = 0; i < n; ++i)
	{
		cin >> montain[i].heigth;
	}
	for (int i = 1; i < n - 1; ++i)
	{
		if (montain[i].heigth > montain[i - 1].heigth&& montain[i].heigth > montain[i + 1].heigth)
		{
			montain[i].peak = true;
			++peakCount;
		}
	}

	if (neededNeighbours > peakCount)
	{
		cout << -1;
	}
	else
	{
		int indexOfFirstPeak = 0;
		int indexOfLastPeak = 0;

		setToNextPeakIndex(&indexOfFirstPeak);
		for (int i = 0; i < neededNeighbours; ++i)
		{
			setToNextPeakIndex(&indexOfLastPeak);
		}

		int min = indexOfLastPeak - indexOfFirstPeak;
		int indexOfMinFirstPeak = indexOfFirstPeak;

		while (indexOfLastPeak != -1)
		{
			setToNextPeakIndex(&indexOfFirstPeak);
			setToNextPeakIndex(&indexOfLastPeak);
			int current = indexOfLastPeak - indexOfFirstPeak;
			if (indexOfLastPeak != -1 && min > current)
			{
				min = current;
				indexOfMinFirstPeak = indexOfFirstPeak;
			}
		}

		neededPeakPositions[0] = indexOfMinFirstPeak + 1;
		for (int i = 1; i < neededNeighbours; i++)
		{
			neededPeakPositions[i] = setToNextPeakIndex(&indexOfMinFirstPeak) + 1;
		}
		cout << min << endl;
		cout << stringJoin(neededPeakPositions, neededNeighbours, " ");
	}

	return 0;
}