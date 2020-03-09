/*
  Test of a class to access the FatFs module
    on Arduino Due by Jean-Michel Gallego
  FatFs module is a generic FAT file system for
    small embedded systems developped by ChaN.  
*/

#include <FatFs.h>

#define POWER_SD_PIN 58 //58 GPIO03
#define POWER_PIN 61 //61 GPIO06
#define RESET_DAC_PIN 62 //62 GPIO07

void setup()
{
  pinMode(RESET_DAC_PIN, OUTPUT);
  pinMode(POWER_PIN, OUTPUT);
  pinMode(POWER_SD_PIN, OUTPUT);
  
  digitalWrite(RESET_DAC_PIN, HIGH);
  digitalWrite(POWER_PIN, HIGH);
  digitalWrite(POWER_SD_PIN, LOW);
  
  int res;

  Serial.begin( 115200 );
  Serial.println( "== Testing FatFs on Arduino ==" );
  Serial.println( "Press a key to start\n" );
  while( Serial.read() < 0 )
    delay( 1 );
  delay( 400 );

  // Mount SD card
  res = FatFs.begin();
  printError( res, "Unable to mount SD card" );
  Serial.println( "SD card mounted" );

  // Show capacity and free space of SD card
  Serial.print( "Capacity of card:   " );
  Serial.print( FatFs.capacity());
  Serial.println( " kBytes" );
  Serial.print( "Free space on card: " );
  Serial.print( FatFs.free());
  Serial.println( " kBytes" );

  // List root directory
  Serial.println( "List of directories and files in root:" );
  DirFs dir;
  if( dir.openDir( "/" ))
    while( dir.nextFile())
    {
      Serial.print( dir.fileName());
      Serial.print( "\t" );
      if( dir.isDir() )
        Serial.println( "(Directory)" );
      else
      {
        Serial.print( dir.fileSize());
        Serial.println( " Bytes" );
      }
    }

  // Create directory
  char * dirName = "/NewDir";
  Serial.print( "\nCreate directory '" );
  Serial.print( dirName );
  Serial.println( "'" );
  if( FatFs.exists( dirName ))
  {
    Serial.print( dirName );
    Serial.println( " already exists!" );
  }
  else
  {
    res = FatFs.mkdir( dirName );
    printError( res, "Error creating directory" );
  }
    Serial.print( dirName );
    Serial.println( " created!" );

  // Create a file in that directory
  FileFs file;
  char * fileName = "/NewDir/TestInDir.txt";
  Serial.print( "\nCreate file '" );
  Serial.print( fileName );
  Serial.println( "'" );
  res = file.open( fileName, FA_WRITE | FA_READ | FA_CREATE_ALWAYS );
  printError( res, "Error creating file" );
  
  // Writing text to a file and closing it
  Serial.println( "Write to file" );
  res = file.writeString( "Test writing to file 1\r\n" );
  if( res >= 0 )
    res = file.writeString( "Testing writing to file 2\r\n" );
  if( res >= 0 )
    res = file.writeString( "Test writing to file 3\r\n" );
  // Write next line using writeBuffer()
  if( res >= 0 )
  {
    char * ps1 = "Test writing to file 4\r\n";
    uint32_t nwrite = file.write( ps1, strlen( ps1 ));
    res = nwrite == strlen( ps1 );
  }
  // Write last line byte per byte,  using writeChar()
  if( res >= 0 )
  {
    char * ps2 = "Byte by byte\r\n";
    uint8_t pc = 0 ;
    while( res >= 0 && ps2[ pc ] != 0 )
      res = file.writeChar( ps2[ pc ++ ] );
  }
  printError( ( res >= 0 ), "Error writing to file" );

  // Read content of file
  Serial.print( "\nContent of '" );
  Serial.print( fileName );
  Serial.println( "' is:" );
  file.seekSet( 0 ); // set cursor to beginning of file
  char line[ 64 ];
  // Read lines with readString() and print length of lines
  int l;
  while( ( l = file.readString( line, sizeof( line ))) >= 0 )
  {
    Serial.print( line );
    Serial.print( " (Length is: " );
    Serial.print( l );
    Serial.println( ")" );
  }

  // Size of the file
  Serial.print( "\nSize of file " );
  Serial.print( fileName );
  Serial.print( " : " );
  Serial.println( file.fileSize());

  // Close the file
  Serial.println( "\nClose the file" );
  res = file.close();
  printError( res, "Error closing file" );

  // Rename and move the file to root
  char * newName = "/TEST.TXT";
  Serial.print( "\nRename file '" );
  Serial.print( fileName );
  Serial.print( "' to '" );
  Serial.print( newName );
  Serial.println( "'" );
  if( FatFs.exists( newName ))
    FatFs.remove( newName );
  res = FatFs.rename( fileName, newName );
  printError( res, "Error renaming file" );

  // Show content of directories
  listDir( dirName );
  listDir( "/" );

  // Copy file
  char * copyName = "/Copy.txt";
  Serial.print( "\nCopy '" );
  Serial.print( newName );
  Serial.print( "' to new file '" );
  Serial.print( copyName );
  Serial.println( "' :" );
  file.open( newName, FA_OPEN_EXISTING | FA_READ );
  FileFs copy;
  res = copy.open( copyName, FA_WRITE | FA_READ | FA_CREATE_ALWAYS );
  printError( res, "Error creating file" );
  uint8_t buf[ 64 ];
  while(( l = file.read( buf, sizeof( buf ))) > 0 )
    if( copy.write( buf, l ) != l )
      printError( res, "Error copying file" );
  copy.close();

  // Open file for reading
  Serial.print( "\nOpen file '" );
  Serial.print( copyName );
  Serial.println( "' :" );
  res = copy.open( copyName, FA_OPEN_EXISTING | FA_READ );
  printError( res, "Error opening file" );

  // Read content of file and close it
  Serial.print( "\nContent of '" );
  Serial.print( copyName );
  Serial.println( "' is:" );
  // Read first line byte per byte, just to demostrate use of readChar()
  char c;
  do
  {
    c = copy.readChar();
    Serial.print( c );
  }
  while( c != '\n' && c != -1 );
  // Read next lines with readString()
  while( copy.readString( line, sizeof( line )) > 0 )
    Serial.println( line );
  copy.close();
    
  // Delete the files
  Serial.print( "\nDelete the files '" );
  Serial.print( newName );
  Serial.print( "' and '" );
  Serial.print( copyName );
  Serial.println( "'" );
  res = FatFs.remove( newName ) || FatFs.remove( copyName );
  printError( res, "Error deleting files" );

  // Delete the directory
  Serial.print( "\nDelete directory '" );
  Serial.print( dirName );
  Serial.println( "'" );
  res = FatFs.rmdir( dirName );
  printError( res, "Error deleting directory" );

  Serial.println( "\nTest ok!" );
}

void loop()
{
}

//    LIST DIRECTORY

void listDir( char * dirname )
{
  DirFs d;
  
  Serial.print( "\nContent of directory '" );
  Serial.print( dirname );
  Serial.println( "' :" );
  if( d.openDir( dirname ))
  {
    uint8_t entrees = 0;
    while( d.nextFile())
    {
      Serial.println( d.fileName());
      entrees ++;
    }
    d.closeDir();
    Serial.print( entrees );
    Serial.print( " files or directories in " );
    Serial.println( dirname );
  }
}

//    PRINT ERROR STRING & STOP EXECUTION

// if ok is false, print the string msg and enter a while loop for ever

void printError( int ok, char * msg )
{
  if( ok )
    return;
  Serial.print( msg );
  Serial.print( ": " );
  Serial.println( FatFs.error());
  while( true )
    delay( 1 );
}
