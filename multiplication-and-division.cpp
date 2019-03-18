#include <string>
#include <iostream>
#include <fstream>

using namespace std;

string killZreos(string strToDo) // Remove zeros from the front. e.g. 0003 -> 3
{
  int count = strToDo.size();
  for (int i = 0; i < count ; i++ )
  {
    if (strToDo[0] == '0')
    {
      strToDo.erase(strToDo.begin());
    }else 
    {
      break;
    }
  }

  return strToDo;
}

string substraction(string line1, string line2)
{
  int n1 = line1.size(); // how many loop
  int n2 = line2.size();

  if (n1 > n2) // Adding zeros to the shorter one
  {
    for (int i = 0; i < n1 - n2; ++i)
    {
      line2.insert(0, "0");
    }
  }
  else if (n1 < n2)
  {
    for (int i = 0; i < n2 - n1; ++i)
    {
      line1.insert(0, "0");
    }
  }

  string res;
  int borrow = 0; // being -1 if borrow 10 from the digit on the left
  for (int i = n1-1; i >= 0; --i)
  {
    int a = (line1[i] - '0') - (line2[i] - '0') + borrow;
    if (a < 0)
    {
      a += 10;
      borrow = -1;
    }else
    {
      borrow = 0;
    }
    res.insert(0, to_string(a)); 
    if (i == 0 && borrow != 0) // if being neg, adding '-'
    {
      res = substraction(line2, line1);
      res = killZreos(res);
      res.insert(0, "-");
    }
  }

  res = killZreos(res);
  return res;
}

string multiply(string line1, string line2)
{
  int n1 = line1.size(); // how many loop
  int n2 = line2.size();
  int res[n1 + n2] = {0};
  int index = 0;
  int countForRes = n1 + n2 -1;
  string resString = "";
  
  for (int i = n1-1; i >= 0; i--) // loop each number of the first number
  {
    int carry = 0;
    int num1 = line1[i] - '0'; // convert char to int

    for (int j = n2-1; j >=  0; j--) // inner loop for second number
    {
      int num2 = line2[j] - '0';
      index = n1+n2-2-i-j; // index for result position, since it's a string starts from 0 to n1+n2-2
      int s = num1 * num2 + res[index] + carry; // temp for everything added.
      carry = s / 10;

      res[index] = s % 10;
    }
    if (carry > 0)
            res[index+1] += carry;
  }

  for (int i = countForRes ; i >= 0; i-- )
  {
    resString.append(to_string(res[i]));
  }

  resString = killZreos(resString);
  return resString;
}

string division(string line1, string line2)
{
  int n1 = line1.size(); // how many loop
  int n2 = line2.size();
  string res;
  string finalQ;
  if (n1 < n2)
  {
    return "0";
  }
  else // n1 >= n2, normal
  {
    string q = ""; // storing (b - a) where b is remainder, a is multiply result
    string b = ""; // temp storage for remainder
    res = line1.substr(0, n2);

    for (int i = n2; i <= n1; i++)
    {
      b = res;
      int z;
      for (z = 0; z < 10; ++z) 
      {
        string a = multiply(line2, to_string(z));
        string c = substraction(b, a); // b-a
        if (c.find("-") == string::npos) //+
        {
          q = c; // let tmp = b-a
        }
        else
        {
          break;
        }
      }
      q.push_back(line1[i]); // push it back
      res = q; // let tmp be real remainder
      res = killZreos(res); // kill additional zeros
      finalQ.append(to_string(z-1)); // generating quotient
    }
  }

  res = killZreos(res);

  finalQ = killZreos(finalQ);

  if(res.compare(line1) == true)
  {
    finalQ = "0";
  }
  cout << "Quotient: " << finalQ << " Remainder: " << res << "\n";
  return res; // return remainder
}

int main()
{
  /**
   *  read lines from file to string line and line2.
   */
  char s[99];
  cout << "Please input the name of file.\n";
  scanf("%s", s);
  ifstream file("input1-3.txt") ;
  string line1;
  string line2; 
  getline(file, line1);
  getline(file, line2);
  cout << "\nMultiplication, A * B =>\n\n" << multiply(line1, line2) << "\n\nDivision, A / B =>\n\n";
  division (line1, line2);
  cout << "\n";
}