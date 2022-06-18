#include<iostream>
using namespace std;
bool deadlockDetectionAlgorithm(int P, int R, int** allocation, int** request, int* available) {
	cout << "     Allocation Matrix\tRequest Matrix\t\tAvailable Matrix" << endl;
	cout << "     ";
	for (int i = 0;i < R;i++) {
		cout << "R" << i + 1 << " ";
	}
	cout << "\t\t";
	for (int i = 0;i < R;i++) {
		cout << "R" << i + 1 << " ";
	}
	cout << "\t\t";
	for (int i = 0;i < R;i++) {
		cout << "R" << i + 1 << " ";
	}
	cout << endl;
	for (int i = 0;i < P;i++) {
		cout << "P" << i + 1 << "   ";
		for (int j = 0;j < R;j++) {
			cout << allocation[i][j] << "  ";
		}
		cout << "\t\t";
		for (int j = 0;j < R;j++) {
			cout << request[i][j] << "  ";
		}
		if (i == 0) {
			cout << "\t\t";
			for (int j = 0;j < R;j++) {
				cout << available[j] << "  ";
			}
		}
		cout << endl;
	}
	int* work = new int[R];
	for (int i = 0;i < R;i++) {
		work[i] = available[i];
	}
	bool* finish = new bool[P];
	for (int i = 0;i < P;i++) {
		bool flag = true;
		for (int j = 0;j < R;j++) {
			if (allocation[i][j] > 0) {
				flag = false;
				break;
			}
		}
		finish[i] = flag;
	}
	int* safeSequence = new int[P];
	int count = 0;
	while (count < P) {
		bool found = false;
		for (int i = 0; i < P; i++) {
			if (finish[i] == false) {
				int j;
				for (j = 0; j < R; j++) {
					if (request[i][j] > work[j]) {
						break;
					}
				}
				if (j == R) {
					for (int k = 0; k < R; k++) {
						work[k] += allocation[i][k];
					}
					safeSequence[count++] = i + 1;
					finish[i] = true;
					found = true;
				}
			}
		}
		if (found == false) {
			cout << "System is not in safe state" << endl;
			cout << "Deadlocked Processes: ";
			for (int x = 0;x < P;x++) {
				if (!finish[x]) {
					cout << "P" << x + 1 << " ";
				}
			}
			cout << endl;
			return false;
		}
	}
	cout << "System is in safe state." << endl;
	cout << "Safe Sequence: ";
	for (int i = 0; i < P; i++) {
		cout << safeSequence[i] << " ";
	}
	cout << endl;
	return true;
}
int main() {
	int P, R;
	cout << "Enter no. of processes: ";
	cin >> P;
	cout << "Enter no. of resources: ";
	cin >> R;
	int* resources = new int[R];
	int* available = new int[R];
	cout << "Enter no. of instances" << endl;
	for (int i = 0;i < R;i++) {
		cout << "R" << i + 1 << ": ";
		cin >> resources[i];
		available[i] = resources[i];
	}
	int** allocation = new int* [P];
	for (int i = 0;i < P;i++) {
		allocation[i] = new int[R];
	}
	int** request = new int* [P];
	for (int i = 0;i < P;i++) {
		request[i] = new int[R];
	}
	cout << "Enter Allocation Matrix" << endl;
	for (int i = 0;i < P;i++) {
		cout << "Process P" << i + 1 << ":" << endl;
		for (int j = 0;j < R;j++) {
			cout << "R" << j + 1 << ": ";
			cin >> allocation[i][j];
			available[j] -= allocation[i][j];
		}
	}
	cout << "Enter Request Matrix" << endl;
	for (int i = 0;i < P;i++) {
		cout << "Process P" << i + 1 << ":" << endl;
		for (int j = 0;j < R;j++) {
			cout << "R" << j + 1 << ": ";
			cin >> request[i][j];
		}
	}
	deadlockDetectionAlgorithm(P, R, allocation, request, available);
	return 0;
}