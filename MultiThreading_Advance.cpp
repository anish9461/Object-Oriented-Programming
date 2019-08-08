//CIS554 HW7
//Name - Anish Nesarkar
//Email - anesarka@syr.edu
//SUID - 368122582
#include <iostream>
#include <ctime>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

mutex m;

condition_variable cv1, cv2;


int prevThread;

bool fa;
bool fb;
bool fc;
bool fd;

int buffer[4]{ 0,0,0,0 };


void PartWorker(int i);
void ProductWorker(int i);

int main()
{
	const int m = 20, n = 20; //m: number of Part Workers
//n: number of Product Workers
//m>n
	thread partW[m];
	thread prodW[n];
	for (int i = 0; i < n; i++) {
		partW[i] = thread(PartWorker, i);
		prodW[i] = thread(ProductWorker, i);
	}
	for (int i = n; i < m; i++) {
		partW[i] = thread(PartWorker, i);
	}
	/* Join the threads to the main threads */
	for (int i = 0; i < n; i++) {
		partW[i].join();
		prodW[i].join();
	}
	for (int i = n; i < m; i++) {
		partW[i].join();
	}
	cout << "Finish!" << endl;
	getchar();
	getchar();
	return 0;
}


//Part Worker
void PartWorker(int i)
{	
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	int iterPart = 1;

	//generate place request
	
	this_thread::sleep_for(chrono::microseconds(2 + ((rand() % 4 ) + 1)));
	for (iterPart = 1; iterPart <= 6; iterPart++)
	{
		
		srand(time(NULL));
		int x = (rand() % 4) + 1;
		int y = (rand() % 4) + 1;
		while (y == x)
			y = (rand() % 4) + 1;

		if ((x == 1 || x == 2) && (y == 2 || y == 1))
		{

			while ((a + b) != 4)
			{
				a = rand() % 4;
				b = rand() % 4;
			}
			c = 0;
			d = 0;

		}

		else if ((x == 1 || x == 3) && (y == 3 || y == 1))
		{
			while (((a + c) != 4))
			{
				a = rand() % 4;
				c = rand() % 4;
			}
			b = 0;
			d = 0;

		}

		else if ((x == 1 || x == 4) && (y == 4 || y == 1))
		{
			while (((a + d) != 4))
			{
				a = rand() % 4;
				d = rand() % 4;
			}
			b = 0;
			c = 0;

		}

		else if ((x == 2 || x == 3) && (y == 3 || y == 2))
		{
			while (((b + c) != 4))
			{
				b = rand() % 4;
				c = rand() % 4;
			}
			a = 0;
			d = 0;

		}

		else if ((x == 2 || x == 4) && (y == 4 || y == 2))
		{
			while (((b + d) != 4))
			{
				b = rand() % 4;
				d = rand() % 4;
			}
			a = 0;
			c = 0;

		}

		else if ((x == 3 || x == 4) && (y == 4 || y == 3))
		{
			while (((c + d) != 4))
			{
				c = rand() % 4;
				d = rand() % 4;
			}
			a = 0;
			b = 0;

		}

		//Put into the buffer

		unique_lock<mutex> ulock(m);
		this_thread::sleep_for(chrono::microseconds(1));
	again:

		//display current buffer state
		cout << endl;
		cout << "Part Worker ID: " << i << endl;
		cout << "Iteration: " << iterPart << endl;
		cout << "Buffer State: (" << buffer[0] << "," << buffer[1] << "," << buffer[2] << "," << buffer[3] << ")" << endl;
		cout << "Place Request: (" << a << "," << b << "," << c << "," << d << ")" << endl;

		fa = false;
		int tempBufValue1 = buffer[0];
		for (int e = buffer[0]; e < 5 && a > 0; e++)
		{
			buffer[0]++;
			cv2.notify_one();
			a--;
			if (buffer[0] == 5)
				fa = true;
		}

		fb = false;
		int tempBufValue2 = buffer[1];
		for (int e = buffer[1]; e < 5 && b > 0; e++)
		{
			buffer[1]++;
			cv2.notify_one();
			b--;
			if (buffer[1] == 5)
				fb = true;
		}
		fc = false;
		int tempBufValue3 = buffer[2];
		for (int e = buffer[2]; e < 4 && c > 0; e++)
		{
			buffer[2]++;
			cv2.notify_one();
			c--;
			if (buffer[2] == 4)
				fc = true;
		}
		fd = false;
		int tempBufValue4 = buffer[3];
		for (int e = buffer[3]; e < 3 && d > 0; e++)
		{
			buffer[3]++;
			cv2.notify_one();
			d--;
			if (buffer[3] == 3)
				fd = true;
		}

		//updated buffer
		cout << "Updated Buffer State: (" << buffer[0] << "," << buffer[1] << "," << buffer[2] << "," << buffer[3] << ")" << endl;
		cout << "Updated Place Request: (" << a << "," << b << "," << c << "," << d << ")" << endl;

		if (tempBufValue1 == buffer[0] && tempBufValue2 == buffer[1] && tempBufValue3 == buffer[2] && tempBufValue4 == buffer[3])
		{
			cout << "Deadlock Detected" << endl;
			cout << "Aborted Iteration: " << iterPart << endl;
			continue;
		}
		else if (prevThread < i)
			continue;

		if ((a == 0) && (b == 0) && (c == 0) && (d == 0))
		{
			continue;
		}

		if (fa == true || fb == true || fc == true || fd == true || (a != 0) || (b != 0) || (c != 0) || (d != 0))
		{
			cv1.wait(ulock);
			goto again;
		}
		
		prevThread = i;

	
	}
	cv1.notify_one();
}


void ProductWorker(int i)
{
	int a=0;
	int b=0;
	int c=0;
	int d=0;
	int iterProduct = 1;
	int deadcount = 0;
	this_thread::sleep_for(chrono::microseconds(2 + ((rand() % 4) + 1)));
	for (iterProduct = 1; iterProduct <= 6; iterProduct++)
	{

		srand(time(NULL));
		int x = (rand() % 4) + 1;
		int y = (x % 4) + 1;
		int z = ((x + y) % 4) + 1;


		if ((x == 1 || x == 2 || x == 3) && (y == 3 || y == 1 || y == 2) && (z == 2 || z == 3 || z == 1))
		{
			while (!((a + b + c) == 4))
			{
				a = rand() % 4;
				b = rand() % 4;
				c = rand() % 4;
			}
			d = 0;
		}

		else if ((x == 2 || x == 4 || x == 3) && (y == 3 || y == 4 || y == 2) && (z == 2 || z == 3 || z == 4))
		{
			while (!((d + b + c) == 4))
			{
				d = rand() % 4;
				b = rand() % 4;
				c = rand() % 4;
			}
			a = 0;
		}

		else if ((x == 1 || x == 4 || x == 3) && (y == 3 || y == 4 || y == 1) && (z == 1 || z == 3 || z == 4))
		{
			while (!((d + a + c) == 4))
			{
				d = rand() % 4;
				a = rand() % 4;
				c = rand() % 4;
			}
			b = 0;
		}

		else if ((x == 2 || x == 4 || x == 1) && (y == 1 || y == 4 || y == 2) && (z == 2 || z == 1 || z == 4))
		{
			while (!((d + b + a) == 4))
			{
				d = rand() % 4;
				b = rand() % 4;
				a = rand() % 4;
			}
			c = 0;
		}


		unique_lock<mutex> ulock(m);
		this_thread::sleep_for(chrono::microseconds(1));
	again:

		//display current buffer state
		cout << endl;
		cout << "Product Worker ID: " << i << endl;
		cout << "Iteration: " << iterProduct << endl;
		cout << "Buffer State: (" << buffer[0] << "," << buffer[1] << "," << buffer[2] << "," << buffer[3] << ")" << endl;
		cout << "Pickup Request: (" << a << "," << b << "," << c << "," << d << ")" << endl;


		fa = false;
		int tempBufValue1 = buffer[0];
		for (int e = buffer[0]; e > 0 && a > 0; e--)
		{
			buffer[0]--;
			cv1.notify_one();
			a--;
			if (buffer[0] == 0)
				fa = true;
		}

		fb = false;
		int tempBufValue2 = buffer[1];
		for (int e = buffer[1]; e > 0 && b > 0; e--)
		{
			buffer[1]--;
			cv1.notify_one();
			b--;
			if (buffer[1] == 0)
				fb = true;
		}
		fc = false;
		int tempBufValue3 = buffer[2];
		for (int e = buffer[2]; e > 0 && c > 0; e--)
		{
			buffer[2]--;
			cv1.notify_one();
			c--;
			if (buffer[2] == 0)
				fc = true;
		}
		fd = false;
		int tempBufValue4 = buffer[3];
		for (int e = buffer[3]; e > 0 && d > 0; e--)
		{
			buffer[3]--;
			cv1.notify_one();
			d--;
			if (buffer[3] == 0)
				fd = true;
		}

		//updated buffer
		cout << "Updated Buffer State: (" << buffer[0] << "," << buffer[1] << "," << buffer[2] << "," << buffer[3] << ")" << endl;
		cout << "Updated Pickup Request: (" << a << "," << b << "," << c << "," << d << ")" << endl;

		if ((tempBufValue1 == buffer[0] && tempBufValue2 == buffer[1] && tempBufValue3 == buffer[2] && tempBufValue4 == buffer[3]))
		{
			cout << "Deadlock Detected" << endl;
			cout << "Aborted Iteration: " << iterProduct << endl;
			continue;
		}
		else if (prevThread < i)
			continue;

		if ((a == 0) && (b == 0) && (c == 0) && (d == 0))
		{
			continue;
		}

		if (fa == true || fb == true || fc == true || fd == true || (a != 0) || (b != 0) || (c != 0) || (d != 0))
		{
			cv2.wait(ulock);
			goto again;
		}
		
		prevThread = i;
	}
	
	cv2.notify_one();
}