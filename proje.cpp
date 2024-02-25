#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class EKGProcessor 
{
private:
    vector<double> timeStamps;
    vector<double> voltages; 
    string personInfo;         

    string classifyEKG(double beatRate)
	{
        if (beatRate >= 0 && beatRate <= 0.5)
            return "Bradycardia";
   		else if (beatRate > 0.5 && beatRate <= 1.5)
            return "Normal";
        else if (beatRate > 1.5)
            return "Tachycardia";
        return "Unknown";
    }

public:
    void readData(const string& filePath)
	{
        ifstream file(filePath.c_str());
        string line;
        double time, voltage;

        if (file.is_open())
		{
            while (getline(file, line)) 
			{
                istringstream iss(line);
                if (iss >> time >> voltage) 
				{
                    timeStamps.push_back(time);
                    voltages.push_back(voltage);
                }
            }
            file.close();
        } else 
            cout << "Dosya açilamadi: " << filePath << endl;
    }

    void analyzeData()
	{
        int numberOfPeaks = 0;
        double totalDuration = timeStamps.back() - timeStamps.front();

        for (size_t i = 1; i < voltages.size() - 1; ++i) 
		{
            if (voltages[i] > voltages[i - 1] && voltages[i] > voltages[i + 1])
                numberOfPeaks++;
        }

        double beatRate = numberOfPeaks / totalDuration * 60;
        personInfo = classifyEKG(beatRate);
    }

    void writeResults(const string& filePath) 
	{
        ofstream outFile(filePath.c_str());
        if (outFile.is_open()) 
		{
            outFile << "Classification: " << personInfo << endl;
            outFile.close();
        } else
            cout << "Dosya yazilirken hata olustu: " << filePath << endl;
    }
};

int main() 
{
    EKGProcessor processor1;
	EKGProcessor processor2;
    string file1 = "person1.txt";
    string file2 = "person2.txt";
    processor1.readData(file1);
    processor1.analyzeData();
    processor1.writeResults("Kisi-1-Result.txt");
    processor2.readData(file2);
    processor2.analyzeData();
    processor2.writeResults("Kisi-2-Result.txt");
    cout << "Operation complete."<< endl;
    return 0;
}

