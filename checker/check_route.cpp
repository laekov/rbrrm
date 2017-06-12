#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main()
{
	freopen("out.txt","r",stdin);
	int m, n, w;
	cin >> m >> n >> w;
	vector <vector<int> > G;
	int rows = m * (w + 1) + 1;
	int cols = n * (w + 1) + 1;

	G.resize(rows + 1);
	for(int i = 0; i < rows; ++i)
		G[i].resize(cols + 1);

	int index1, index2;
	while(cin >> index1 >> index2)
	{
		int x1 = index1 >> 16;
		int y1 = index1 & 0xffff;
		int x2 = index2 >> 16;
		int y2 = index2 & 0xffff;
		G[x1][y1] ++;
		G[x2][y2] ++;
	}
	
	/*debug drawing degrees

	for(int i = 0; i < rows; ++i)
	{
		for(int j = 0; j < cols; ++j)
			cout << G[i][j] << " ";
		cout << endl;
	}*/

	int i, j;
	bool flag = true;
	for( i = 0; i < rows; ++i)
		if(!flag) break;
		else
		for( j = 0; j < cols; ++j)
			if(i > 0 && i < rows - 1 && j > 0 && j < cols - 1) //inside
			{
				if(i % (w + 1) == 0 && j % (w + 1) == 0) //is a pole
				{
					if(G[i][j] != 1)
					{
						flag = false;
						cout << "case1" << endl;
						break;
					}
				}
				else
				if (G[i][j] % 2)
				{
					flag = false;
					cout << "case2" << endl;
					break;
				}
			}

	if(flag)
		cout << "Checked. No problem" << endl;
	else
		cout << "Error occured! At (" << i << "," << j << ")." << endl;

}
