#include <bits/stdc++.h>

using namespace std;

int numRows;
int idx;
int numColumns;
string dFormat;
char bitmap[200][200];

inline void convertToDFormat(int top, int bottom, int left, int right)
{
	if(bottom < top or right < left)
		return;
	idx = (idx + 1) % 50;

	if(bottom == top and left == right)
	{
		cout << bitmap[top][left];
		if(!idx)
			cout << "\n";
		return;
	}

	int zeros = 0;
	int width = right - left + 1;
	int height = bottom - top + 1;

	for(int i = top; i <= bottom; ++i)
		zeros += count(bitmap[i] + left, bitmap[i] + right + 1, '0');

	if(!zeros)
	{
		cout << '1';
		if(!idx)
			cout << "\n";
	}
	else if(zeros == width * height)
	{
		cout << '0';
		if(!idx)
			cout << "\n";
	}
	else
	{
		cout << 'D';
		if(!idx)
			cout << "\n";
		int halfW = ceil((float)(left + right + 1) / 2.0) - 1;
		int halfH = ceil((float)(top + bottom + 1) / 2.0) - 1;

		convertToDFormat(top, halfH, left, halfW);
		convertToDFormat(top, halfH, halfW + 1, right);
		convertToDFormat(halfH + 1, bottom, left, halfW);
		convertToDFormat(halfH + 1, bottom, halfW + 1, right);
	}

	return;
}

inline void convertToBFormat(int top, int bottom, int left, int right)
{
	if(bottom < top or right < left)
		return;

	++idx;

	if(bottom == top and left == right)
	{
		bitmap[top][left] = dFormat[idx];
		return;
	}

	int width = right - left + 1;
	int height = bottom - top + 1;

	if(dFormat[idx] == '1' or dFormat[idx] == '0')
	{
		for(int i = top; i <= bottom; ++i)
			memset(bitmap[i] + left, dFormat[idx], width);
	}
	else
	{
		int halfW = ceil((float)(left + right + 1) / 2.0) - 1;
		int halfH = ceil((float)(top + bottom + 1) / 2.0) - 1;

		convertToBFormat(top, halfH, left, halfW);
		convertToBFormat(top, halfH, halfW + 1, right);
		convertToBFormat(halfH + 1, bottom, left, halfW);
		convertToBFormat(halfH + 1, bottom, halfW + 1, right);
	}

	return;
}

int main(void)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);


	char technique;
	while(cin >> technique and technique != '#')
	{
		cin >> numRows >> numColumns;

		cout << (technique == 'D'?'B':'D') << setw(4) << numRows << setw(4) << numColumns << "\n";

		if(technique == 'B')
		{
			for(int i = 0; i < numRows; ++i)
			{
				char bit;
				for(int j = 0; j < numColumns; ++j)
					cin >> bitmap[i][j];
			}
			idx = 0;
			convertToDFormat(0, numRows - 1, 0, numColumns - 1);
		}
		else
		{
			idx = -1;
			cin >> dFormat;

			convertToBFormat(0, numRows - 1, 0, numColumns - 1);

			idx = 1;
			for(int i = 0; i < numRows; ++i)
			{
				for(int j = 0; j < numColumns; ++j, idx = (idx + 1) % 50)
				{
					cout << bitmap[i][j];
					if(!idx and (numRows - i - 1) * numColumns + (numColumns - j - 1))
						cout << "\n";
				}
			}
		}
		cout << "\n";
	}

	return 0;
}