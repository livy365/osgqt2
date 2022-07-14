#include<iostream>
#include<string>
#include<fstream>
#include<vector>

int readtext(std::string file,bool first,bool last)
{

	using namespace std;
	ifstream text;
	text.open(file, ios::in);
	vector<double> strVec;
	ofstream readx, readz, ready, readc, reada;
	if (first)
	{
		readx.open("readx.txt", ios_base::out);
		readz.open("readz.txt", ios_base::out);
		ready.open("ready.txt", ios_base::out);
		reada.open("reada.txt", ios_base::out );
		readc.open("readc.txt", ios_base::out );
	}
	else
	{

	readx.open("readx.txt", ios_base::out|ios_base::app);
	readz.open("readz.txt", ios_base::out | ios_base::app);
	ready.open("ready.txt", ios_base::out | ios_base::app);
	reada.open("reada.txt", ios_base::out | ios_base::app);
	readc.open("readc.txt", ios_base::out | ios_base::app);
	}


	string g, x, z, f, t, n, y, a, c;
	x = "300";
	z = "1";
	while (!text.eof())
	{
		string inbuf;
		getline(text, inbuf, '\n');
		if (inbuf.size() != 0) {
			//cout << inbuf << endl;
		}
		auto pd = inbuf.begin();




		for (pd; pd != inbuf.end(); pd++)
		{
			//cout << *pd << endl;
			if (*pd == 'N')
			{
				n.clear();
				pd++;
				while (!(*pd >= 'A' && *pd <= 'Z'))
				{
					//pd++;
					if (*pd == '.' && !(*(pd - 1) >= '0' && *(pd - 1) <= '9'))
					{
						n.push_back('0');
					}
					n.push_back(*pd);
					pd++;
					if (pd == inbuf.end())
					{
						//cout << "end"<< endl;
						pd--;
						break;
					}

				}
				try
				{
					double res = stoi(n);

				}
				catch (const std::invalid_argument& e)	// 捕获 std::invalid_argument 异常
				{								// 这时在对异常进行处理
					std::cerr << e.what() << endl; std::cout << inbuf << endl;// 输出是什么异常
					// some code response to this exception，作出处理
				}
				catch (const std::out_of_range& e)	// 捕获 std::out_of_range 异常
				{								// 这时在对异常进行处理
					std::cerr << e.what() << endl;
					// some code response to this exception，作出处理
				}

			}
			if (*pd == 'T')
			{
				t.clear();
				pd++;
				while (!(*pd >= 'A' && *pd <= 'Z'))
				{
					//pd++;
					if (*pd == '.' && !(*(pd - 1) >= '0' && *(pd - 1) <= '9'))
					{
						t.push_back('0');
					}
					t.push_back(*pd);
					pd++;
					if (pd == inbuf.end())
					{
						//cout << "end"<< endl;
						pd--;
						break;
					}

				}
				try
				{
					double res = stoi(t);
					//cout << "t" << t << endl;
				}
				catch (const std::invalid_argument& e)	// 捕获 std::invalid_argument 异常
				{								// 这时在对异常进行处理
					std::cerr << e.what() << endl; std::cout << inbuf << endl; // 输出是什么异常
					// some code response to this exception，作出处理
				}
				catch (const std::out_of_range& e)	// 捕获 std::out_of_range 异常
				{								// 这时在对异常进行处理
					std::cerr << e.what() << endl;
					// some code response to this exception，作出处理
				}

			}

			if (*pd == 'G')
			{
				g.clear();
				pd++;
				while (!(*pd >= 'A' && *pd <= 'Z'))
				{
					//pd++;
					if (*pd == '.' && !(*(pd - 1) >= '0' && *(pd - 1) <= '9'))
					{
						g.push_back('0');
					}
					g.push_back(*pd);
					pd++;
					if (pd == inbuf.end())
					{
						//cout << "end"<< endl;
						pd--;
						break;
					}

				}
				try
				{
					double res = stoi(g);
					//cout << "g" << g << endl;
				}
				catch (const std::invalid_argument& e)	// 捕获 std::invalid_argument 异常
				{								// 这时在对异常进行处理
					std::cerr << e.what() << endl; std::cout << inbuf << endl; // 输出是什么异常
					// some code response to this exception，作出处理
				}
				catch (const std::out_of_range& e)	// 捕获 std::out_of_range 异常
				{								// 这时在对异常进行处理
					std::cerr << e.what() << endl;
					// some code response to this exception，作出处理
				}

			}

			if (*pd == 'X')
			{
				x.clear();
				pd++;
				while (!(*pd >= 'A' && *pd <= 'Z'))
				{
					//pd++;
					if (*pd == '.' && !(*(pd - 1) >= '0' && *(pd - 1) <= '9'))
					{
						x.push_back('0');
					}
					x.push_back(*pd);
					pd++;
					if (pd == inbuf.end())
					{
						//cout << "end"<< endl;
						pd--;
						break;
					}

				}
				try
				{
					double res = stoi(x);
					//cout << "x" << x << endl;
				}
				catch (const std::invalid_argument& e)	// 捕获 std::invalid_argument 异常
				{								// 这时在对异常进行处理
					std::cerr << e.what() << endl; std::cout << inbuf << endl; // 输出是什么异常
					// some code response to this exception，作出处理
				}
				catch (const std::out_of_range& e)	// 捕获 std::out_of_range 异常
				{								// 这时在对异常进行处理
					std::cerr << e.what() << endl;
					// some code response to this exception，作出处理
				}

			}
			if (*pd == 'Y')
			{
				y.clear();
				pd++;
				while (!(*pd >= 'A' && *pd <= 'Z'))
				{
					//pd++;
					if (*pd == '.' && !(*(pd - 1) >= '0' && *(pd - 1) <= '9'))
					{
						y.push_back('0');
					}
					y.push_back(*pd);
					pd++;
					if (pd == inbuf.end())
					{
						//cout << "end"<< endl;
						pd--;
						break;
					}

				}
				try
				{
					double res = stoi(y);
					//cout << "z" << z << endl;
				}
				catch (const std::invalid_argument& e)	// 捕获 std::invalid_argument 异常
				{								// 这时在对异常进行处理
					std::cerr << e.what() << endl; std::cout << inbuf << endl; // 输出是什么异常
					// some code response to this exception，作出处理
				}
				catch (const std::out_of_range& e)	// 捕获 std::out_of_range 异常
				{								// 这时在对异常进行处理
					std::cerr << e.what() << endl;
					// some code response to this exception，作出处理
				}

			}


			if (*pd == 'Z')
			{
				z.clear();
				pd++;
				while (!(*pd >= 'A' && *pd <= 'Z'))
				{
					//pd++;
					if (*pd == '.' && !(*(pd - 1) >= '0' && *(pd - 1) <= '9'))
					{
						z.push_back('0');
					}
					z.push_back(*pd);
					pd++;
					if (pd == inbuf.end())
					{
						//cout << "end"<< endl;
						pd--;
						break;
					}

				}
				try
				{
					double res = stoi(z);
					//cout << "z" << z << endl;
				}
				catch (const std::invalid_argument& e)	// 捕获 std::invalid_argument 异常
				{								// 这时在对异常进行处理
					std::cerr << e.what() << endl; std::cout << inbuf << endl; // 输出是什么异常
					// some code response to this exception，作出处理
				}
				catch (const std::out_of_range& e)	// 捕获 std::out_of_range 异常
				{								// 这时在对异常进行处理
					std::cerr << e.what() << endl;
					// some code response to this exception，作出处理
				}

			}
			if (*pd == 'A')
			{
				a.clear();
				pd++;
				while (!(*pd >= 'A' && *pd <= 'Z'))
				{
					//pd++;
					if (*pd == '.' && !(*(pd - 1) >= '0' && *(pd - 1) <= '9'))
					{
						a.push_back('0');
					}
					a.push_back(*pd);
					pd++;
					if (pd == inbuf.end())
					{
						//cout << "end"<< endl;
						pd--;
						break;
					}

				}
				try
				{
					double res = stoi(a);
					//cout << "z" << z << endl;
				}
				catch (const std::invalid_argument& e)	// 捕获 std::invalid_argument 异常
				{								// 这时在对异常进行处理
					std::cerr << e.what() << endl; std::cout << inbuf << endl; // 输出是什么异常
					// some code response to this exception，作出处理
				}
				catch (const std::out_of_range& e)	// 捕获 std::out_of_range 异常
				{								// 这时在对异常进行处理
					std::cerr << e.what() << endl;
					// some code response to this exception，作出处理
				}

			}
			if (*pd == 'C')
			{
				c.clear();
				pd++;
				while (!(*pd >= 'A' && *pd <= 'Z'))
				{
					//pd++;
					if (*pd == '.' && !(*(pd - 1) >= '0' && *(pd - 1) <= '9'))
					{
						c.push_back('0');
					}
					c.push_back(*pd);
					pd++;
					if (pd == inbuf.end())
					{
						//cout << "end"<< endl;
						pd--;
						break;
					}

				}
				try
				{
					double res = stoi(c);
					//cout << "z" << z << endl;
				}
				catch (const std::invalid_argument& e)	// 捕获 std::invalid_argument 异常
				{								// 这时在对异常进行处理
					std::cerr << e.what() << endl; std::cout << inbuf << endl; // 输出是什么异常
					// some code response to this exception，作出处理
				}
				catch (const std::out_of_range& e)	// 捕获 std::out_of_range 异常
				{								// 这时在对异常进行处理
					std::cerr << e.what() << endl;
					// some code response to this exception，作出处理
				}

			}

			if (*pd == 'F')
			{
				f.clear();
				pd++;
				while (!(*pd >= 'A' && *pd <= 'Z'))
				{
					//pd++;
					if (*pd == '.' && !(*(pd - 1) >= '0' && *(pd - 1) <= '9'))
					{
						f.push_back('0');
					}
					f.push_back(*pd);
					pd++;
					if (pd == inbuf.end())
					{
						//cout << "end"<< endl;
						pd--;
						break;
					}

				}
				try
				{
					double res = stoi(f);
					//cout << "f" << f << endl;
				}
				catch (const std::invalid_argument& e)	// 捕获 std::invalid_argument 异常
				{								// 这时在对异常进行处理
					std::cerr << e.what() << endl; std::cout << inbuf << endl; // 输出是什么异常
					// some code response to this exception，作出处理
				}
				catch (const std::out_of_range& e)	// 捕获 std::out_of_range 异常
				{								// 这时在对异常进行处理
					std::cerr << e.what() << endl;
					// some code response to this exception，作出处理
				}

			}

		}

		if (!text.eof()||!last)
		{
			readx << x << endl;
			readz << z << endl;
			ready << y << endl;
			reada << a << endl;
			readc << c << endl;
		}
		else
		{
			readx << x;
			readz << z;
			ready << y;
			reada << a;
			readc << c;
		}


	}


	readx.close();
	readz.close();
	ready.close();
	reada.close();
	readc.close();

	return 0;
}