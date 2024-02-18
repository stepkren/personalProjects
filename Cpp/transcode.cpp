#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

string ByteToBinary ( const int32_t content )
{
    unsigned char u_content = content;
    uint32_t value = u_content; int remainder = 0; char tmp = 0;
    string res = "";
    while ( 1 ){
        if ( value == 0 )
            break;
        remainder = value % 2;
        value /= 2;
        if ( remainder == 0 )
            tmp = '0';
        else if ( remainder == 1 )
            tmp = '1';
        res = tmp + res;
    }
    if ( res.length() < 8 ){
        while ( res.length() != 8 ){
           res = '0' + res;;
        }
    }

    return res;
}   

vector<int32_t> GenerateFibSeq ( void )
{
    vector<int32_t> fibSeq;
    int a = 1;
    int b = 2;
    int c = 0;
    int max = 1114111;

    fibSeq.push_back( a );
    fibSeq.push_back( b );

    while ( b < max ){
        int tmp = b;
        c = a + b;
        b = c;
        a = tmp;
        
        fibSeq.push_back( c );
    }

    return fibSeq;
}

int NumberOfExtraBytes ( int32_t &value )
{
    int n = 0;
    if ( ( value & 0b11111000 ) == 0b11110000 ){
        value = ( value & 0b00000111 );
        n = 3;
    }
    else if ( ( value & 0b11110000 ) == 0b11100000 ){
        value = ( value & 0b00001111 );
        n = 2;
    }
    else if ( ( value & 0b11100000 ) == 0b11000000 ){
        value = ( value & 0b00011111 );
        n = 1;
    }
    else if ( ( value & 0b10000000 ) == 0b00000000 ){
        value = ( value & 0b01111111 );
        n = 0;
    }
    else { n = -1; }

    return n;  
}

void RotateString ( string &tmp )
{
    int j = tmp.length() - 1;
    int i = 0;

    for ( size_t q = 0; q < tmp.length() / 2; q++ ){
        char tmp_char = tmp[i];
        tmp[i] = tmp[j]; tmp[j] = tmp_char;
        i++; j--;
    }
}

bool WriteOutputToFile ( string &finalSeq, ofstream &outputFile )
{
    size_t position = 0; size_t lengthOfSubstr = 8; string tmp = ""; char outputByte = 0;
    while ( position < finalSeq.length() ){
        tmp = finalSeq.substr( position, lengthOfSubstr );
        RotateString ( tmp );
        // cout << "tmp = " << tmp << endl;
        position += lengthOfSubstr;
        outputByte = stoi ( tmp, 0, 2 );
        outputFile << outputByte;
        if ( ! ( outputFile.good() ) )
            return false;
    }
    finalSeq = "";
    return true;
}

bool ToFib ( const vector<int32_t> &FS, int32_t value, ofstream &outputFile, string &finalSeq )
{
    size_t i = FS.size();
    value += 1; string value_fib = "";
    while ( 1 ){
        if ( (value >= FS[i - 1]) && (value <= FS[i]) )
            break; 
        i--;
    }

    i++;
    for ( size_t j = i; j > 0; j-- ){
        if ( ( FS [j - 1] >= value ) && ( j == size_t(i) ) ){
            value_fib = '1' + value_fib;
            continue;
        }
        if ( FS [j - 1] > value ){
            value_fib = '0' + value_fib;
        }
        if ( FS [j - 1] <= value ){
            value_fib = '1' + value_fib;
            value -= FS [j - 1];
        }
    }
    finalSeq += value_fib;

    if ( ( finalSeq.length() % 8 ) == 0 ){
        if ( ! (WriteOutputToFile ( finalSeq, outputFile ) ) )
            return false;
    }

    return true;
}

bool CompleteOutput ( string &finalSeq, ofstream &outputFile )
{
    if ( finalSeq.length() > 0 ){
        if ( ! ( WriteOutputToFile ( finalSeq, outputFile ) ) )
            return false;        
    }
    return true;
}

bool RemoveMask ( int32_t &value )
{
    if ( ( value & 0b11000000 ) != 0b10000000 )
        return false;
    value = ( value & 0b00111111 );

    return true;
}

int32_t BitwiseOr ( int32_t value1, int32_t value2 )
{
    int32_t finalByte = ( ( value1 << 6 ) | value2 );

    return finalByte;
}

bool utf8ToFibonacci ( const char * inFile, const char * outFile )
{
    ifstream inputFile ( inFile, ios::binary );
    if ( ! ( inputFile.is_open() && inputFile.good() ) )
        return false;

    ofstream outputFile ( outFile, ios::binary );
    if ( ! ( outputFile.is_open() && outputFile.good() ) )
        return false;
    char content = 0; vector<int32_t> FS = GenerateFibSeq(); string finalSeq = "";
    while ( inputFile.get( content ) ){
        string contentBinary = ByteToBinary ( content );
        int32_t value = stoi ( contentBinary, 0, 2 );
        int numOfExtraBytes = NumberOfExtraBytes ( value );
        if ( numOfExtraBytes == 0 ){
            if ( ! ( ToFib ( FS, value, outputFile, finalSeq ) ) )
                return false;
        }
        else if ( ( numOfExtraBytes > 0 ) && ( numOfExtraBytes < 4 ) ){
            for ( int i = 0; i < numOfExtraBytes; i++ ){
                inputFile.get ( content );
                if ( inputFile.eof() )
                    return false;
                string contentBinary = ByteToBinary ( content );
                int32_t value2 = stoi ( contentBinary, 0, 2 );
                if ( ! ( RemoveMask ( value2 ) ) )
                    return false;
                if ( value2 > 63 )
                    return false;
                value = BitwiseOr( value, value2 );
            }
            if ( ! ( ToFib ( FS, value, outputFile, finalSeq ) ) )
                return false;
        }
        else return false;

    }
    if ( ! ( CompleteOutput ( finalSeq, outputFile ) ) )
        return false;

    return true;
}


int FoundSeqToNum ( const string &foundSeq, vector<int32_t> FS )
{
    int value = 0;
    for ( size_t i = 0; i < foundSeq.length(); i++ ){
        if ( foundSeq[i] == '1' ){
            value += FS[i];
        }
    }

    return value - 1;
}

int NumOfBytes ( const int32_t value )
{
    int n = 0;

    if ( ( value >= 0 ) && ( value <= 127 ) )
        n = 0;
    else if ( ( value >= 128 ) && ( value <= 2047 ) )
        n = 1;
    else if ( ( value >= 2048 ) && ( value <= 65535 ) )
        n = 2;
    else if ( ( value >= 65536 ) && ( value <= 1114111 ) )
        n = 3;
    else 
        n = -1;

    return n;
}

string ToBinary ( int32_t value )
{
    string res = ""; int tmp = value;

    while ( 1 ){
        if ( tmp == 0 )
            break;
        int remainder = tmp % 2;
        if (remainder == 0)
            res = '0' + res;
        else if ( remainder == 1 )
            res = '1' + res;
        tmp /= 2;
    }

    return res;
}

void FillWithZeros ( string &finalSeq, const int numOfBytes )
{
    size_t length = 0;
    if ( numOfBytes == 1 ){
        length = 6;
        while ( finalSeq.length() != length ){
            finalSeq = '0' + finalSeq;
        }
    }
    else if ( numOfBytes == 2 ){
        length = 12;
        while ( finalSeq.length() != length ){
            finalSeq = '0' + finalSeq;
        }
    }
    else if ( numOfBytes == 3 ){
        length = 18;
        while ( finalSeq.length() != length ){
            finalSeq = '0' + finalSeq;
        }
    }
}

bool ToUtf8 ( int32_t value, ofstream &outputFile )
{
    int numOfBytes = NumOfBytes( value );
    if ( numOfBytes == -1 )
        return false;

    if ( numOfBytes == 0 ){
        if ( value > 127 )
            return false;
        char finalByte = value;
        outputFile << finalByte;
        if ( ! ( outputFile.good() ) )
            return false;
    }
    else{
        size_t position = 0; 
        string finalSeq = ToBinary ( value );
        string tmp = ""; char finalByte = 0; int32_t tmp_int = 0;
        if ( numOfBytes == 1 ){
            if ( finalSeq.length() < 6 ){
                FillWithZeros ( finalSeq, numOfBytes );
            }
            tmp = finalSeq.substr ( position, finalSeq.length() % 6 );
            if ( tmp.length() == 0 )
                tmp_int = 0;
            else
                tmp_int = stoi ( tmp, 0, 2 );
            if ( ( tmp_int > 0b11011111 ) )
                return false;
            tmp_int |= 0b11000000;
            position += finalSeq.length() % 6;
            finalByte = tmp_int;
        }
        else if ( numOfBytes == 2 ){
            if ( finalSeq.length() < 12 ){
                FillWithZeros ( finalSeq, numOfBytes );
            }            
            tmp = finalSeq.substr ( position, finalSeq.length() % 6 );
            if ( tmp.length() == 0 )
                tmp_int = 0;
            else            
                tmp_int = stoi ( tmp, 0, 2 );
            if ( ( tmp_int > 0b11101111 ) )
                return false;            
            tmp_int |= 0b11100000;
            position += finalSeq.length() % 6;
            finalByte = tmp_int;
        }
        else if ( numOfBytes == 3 ){
            if ( finalSeq.length() < 18 ){
                FillWithZeros ( finalSeq, numOfBytes );
            }            
            tmp = finalSeq.substr ( position, finalSeq.length() % 6 );
            if ( tmp.length() == 0 )
                tmp_int = 0;
            else            
                tmp_int = stoi ( tmp, 0, 2 );
            if ( ( tmp_int > 0b11110111 ) )
                return false;            
            tmp_int |= 0b11110000;
            position += finalSeq.length() % 6;
            finalByte = tmp_int;
        }       
        outputFile << finalByte;
        if ( ! ( outputFile.good() ) )
            return false;

        for ( int i = 0; i < numOfBytes; i++ ){
            tmp = finalSeq.substr( position, 6 );
            if ( tmp.length() == 0 )
                tmp_int = 0;
            else            
                finalByte = stoi( tmp, 0, 2 );
            if ( ( finalByte > 0b10111111 ) )
                return false;
            finalByte |= 0b10000000;
            position += 6;
            outputFile << finalByte;
            if ( ! ( outputFile.good() ) )
                return false;
        }        
    }

    return true;
}

bool SplitSeqByDoubleOnes ( const string &byte, ofstream &outputFile, string &remainingString, const vector<int32_t> &FS )
{   
    string foundSeq = ""; size_t position = 0;
    for ( size_t i = 0; i < byte.length(); i++ ){
        if ( ( byte[i - 1] == '1' ) && ( byte[i] == '1' ) ){
            foundSeq = byte.substr( position, ( i - position ) );
            int32_t value = FoundSeqToNum ( foundSeq, FS );
            if ( ! ( ToUtf8( value, outputFile ) ) )
                return false;
            position += foundSeq.length() + 1; i++;
        }
    }
    remainingString = byte.substr( position, byte.length() - position );

    return true;
}

bool CheckRemaining ( const string &remainingSeq )
{
    for ( size_t i = 0; i < remainingSeq.length(); i++ ){
        if ( remainingSeq[i] == '1' )
            return false;
    }

    return true;
}

bool               fibonacciToUtf8                         ( const char      * inFile, 
                                                             const char      * outFile )
{
    ifstream inputFile ( inFile );
    if ( ! ( inputFile.is_open() && inputFile.good() ) )
        return false;

    ofstream outputFile ( outFile );
        if ( ! ( outputFile.is_open() && outputFile.good() ) )
            return false;
    char content = 0; vector<int32_t> FS = GenerateFibSeq(); string finalSeq = ""; string bitsString = "";
    string foundSeq = ""; string remainingString = "";
    for ( size_t i = 0; i < FS.size(); i++ ){
    }
    while ( inputFile.get ( content ) ){
        string contentBinary = ByteToBinary ( content );
        RotateString ( contentBinary );
        bitsString = remainingString + contentBinary;
        if ( ! ( SplitSeqByDoubleOnes ( bitsString, outputFile, remainingString, FS ) ) )
            return false; 

    }
    if ( ! ( CheckRemaining ( remainingString ) ) )
        return false;


    return true;
}
  


int main ( int argc, char * argv [] )
{
  assert ( utf8ToFibonacci ( "example/src_0.utf8", "output.fib" )
           && identicalFiles ( "output.fib", "example/dst_0.fib" ) );
  assert ( utf8ToFibonacci ( "example/src_1.utf8", "output.fib" )
           && identicalFiles ( "output.fib", "example/dst_1.fib" ) );
  assert ( utf8ToFibonacci ( "example/src_2.utf8", "output.fib" )
           && identicalFiles ( "output.fib", "example/dst_2.fib" ) );
  assert ( utf8ToFibonacci ( "example/src_3.utf8", "output.fib" )
           && identicalFiles ( "output.fib", "example/dst_3.fib" ) );
  assert ( utf8ToFibonacci ( "example/src_4.utf8", "output.fib" )
           && identicalFiles ( "output.fib", "example/dst_4.fib" ) );
  assert ( ! utf8ToFibonacci ( "example/src_5.utf8", "output.fib" ) );

  assert ( fibonacciToUtf8 ( "example/src_6.fib", "output.utf8" )
           && identicalFiles ( "output.utf8", "example/dst_6.utf8" ) );
  assert ( fibonacciToUtf8 ( "example/src_7.fib", "output.utf8" )
           && identicalFiles ( "output.utf8", "example/dst_7.utf8" ) );
  assert ( fibonacciToUtf8 ( "example/src_8.fib", "output.utf8" )
           && identicalFiles ( "output.utf8", "example/dst_8.utf8" ) );
  assert ( fibonacciToUtf8 ( "example/src_9.fib", "output.utf8" )
           && identicalFiles ( "output.utf8", "example/dst_9.utf8" ) );
  assert ( fibonacciToUtf8 ( "example/src_10.fib", "output.utf8" )
           && identicalFiles ( "output.utf8", "example/dst_10.utf8" ) );
  assert ( ! fibonacciToUtf8 ( "example/src_11.fib", "output.utf8" ) );


  
 
  return EXIT_SUCCESS;
}
