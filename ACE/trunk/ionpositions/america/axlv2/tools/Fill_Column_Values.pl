#! /usr/bin/perl
#
# File:  fill_column_values.pl
#
# Description:
#   Takes a file and fills a particular column within a given number of
#   rows with a fill value. For example, in an Iron charge distribution file,
#   the relative abundance column is filled with the default fill value 
#   from time 183.08 to time 183.09.
#
#  Interval File Format:
#  # <-- Comment at beginning of line
#  123.01  123.34   <-- 1-3 digit number, decimal point, 2 digit number, 
#                       spaces, repeat once. 
#                             First number is the start point (inclusive)
#                             Second number is the end point (inclusive)
#
# Author(s):  Nick Montgomery (ndm)
#
# Methods/Subroutines:
#         main
#         open_files
#         create_hash_from_intervals
#
# Revision controlled by CVS:
#
#
# Major Modification History:
#
#

##############
# perl setup #
##############
package Fill_Column_Values;
use strict;
use warnings;
use Getopt::Long;
use File::Copy;
our $thisPackage = "Fill_Column_Values";

#######################
# ===> configure <=== #
#######################\
### PSEUDO CONSTANTS###
#Defaults
my $DEFAULT_TEMP_FILE = "Fill_Column_Values.tempfile." . time();
my $DEFAULT_INTERVAL_FILE = "intervals.txt";
my $DEFAULT_OUTPUT_FILE_EXTENSION = ".filled";
my $DEFAULT_FILL_VALUE = "-1.00e+00";

# location to store temporary files
# typical: "/tmp"
my $TEMP_DIR = "/tmp";


#input file split character
my $INPUT_NAME_SPLIT_CHARACTER = "_";

#input file type column
my $INPUT_FILE_TYPE_COLUMN = 3; #4th token/column

#input file types hash table (stores the fill and time column numbers)
my %INPUT_COLUMNS = (
			"qdist" => {"fill" => 4,
				    "time" => 1},
);


###########################
# ===> end configure <=== #
###########################

##########################
#==>  Inline Commands <==#
##########################
##
#Description: This section gets and verifies the arguments to the program
#             before calling main subroutine
##

#Declare final input variables as local
my ($inputFile, $intervalFile, $reuseInput, $outputFile, $tempFile,
    $useVerbose, $fillValue);
#Declare argument variables as local
my ($argInputFile, $argIntervalFile, $argReuseInput, 
    $argOutputFile, $argTempFile, $argVerbose, $argFillValue, $argHelp);

#Get command line options
my $commandLineOptions =
"The following is the parameter format:\n"
."--input_file     = [File] (required)\n"
."--interval_file  = [File] (Default: $DEFAULT_INTERVAL_FILE)\n"
."--reuse_input      Use if the input file should also be the output file "
                     ."(default=no)\n"
."--output_file    = [File] (Default: input_file"
                           ."$DEFAULT_OUTPUT_FILE_EXTENSION)\n"
."--temp_file      = [File] (Default: $TEMP_DIR/$DEFAULT_TEMP_FILE)\n"
."--fill_value     = [Value] (Default: $DEFAULT_FILL_VALUE)\n"
."--verbose          Use if you wan't verbose output\n"
."--help             Use to display this help screen\n"
."\n\n";

GetOptions("input_file=s"   => \$argInputFile,
	  "interval_file=s" => \$argIntervalFile,
	  "reuse_input"     => \$argReuseInput,
	  "output_file=s"   => \$argOutputFile,
	  "temp_file=s"     => \$argTempFile,
	  "fill_value=s"    => \$argFillValue,
	  "verbose"         => \$argVerbose,
	  "help"            => \$argHelp);

#are command line options correct? If not, exit and writeout options
#if they are correct, set the variables appropriately

#help output (end program)
if (defined($argHelp)){
  die "\n\nUsage: $thisPackage \[OPTIONS\]\n\n"
       ."OPTIONS:\n$commandLineOptions";
}

#input file
if (defined($argInputFile)) {$inputFile = $argInputFile;}
else {die "\n\nNo Input file (--input_file) specified!\n"
	 ."\n$commandLineOptions";}

#interval file
if (defined($argIntervalFile)) {$intervalFile = $argIntervalFile;}
else {$intervalFile = $DEFAULT_INTERVAL_FILE;}

#if reuse input is not set, use the output file for output
if (defined ($argReuseInput)) { 
  $outputFile = $inputFile;
}
else {
  if (defined ($argOutputFile)) { $outputFile = $argOutputFile;}
  else { $outputFile = $inputFile .$DEFAULT_OUTPUT_FILE_EXTENSION;}
}

#tempfile
if (defined($argTempFile)) {$tempFile = $argTempFile;}
else {$tempFile = "$TEMP_DIR/$DEFAULT_TEMP_FILE";}

#fill_value
if (defined($argFillValue)) {$fillValue = $argFillValue;}
else {$fillValue = "$DEFAULT_FILL_VALUE";}

#verbose
if (defined($argVerbose)) {$useVerbose = 1;}
else {$useVerbose=undef();}

#writeout command line options that user inputted
print "\nRunning Program: $thisPackage\n"
     ."InputFile:       $inputFile\n"
     ."IntervalFile:    $intervalFile\n"
     ."TempFile:        $tempFile\n"
     ."OutputFile:      $outputFile\n";
print "Using Verbose Output" if defined($useVerbose);
print "\n\n\n";


#Run main program
if (main ($inputFile, $intervalFile, $tempFile, $outputFile, $useVerbose, 
	  $fillValue)) {print "Exiting following successful completion.\n";}
else {print "Exiting following failure.\n";}


##########################
#> End Inline Commands  <#
##########################


#################################
##                             ##
##        MAIN FUNCTION        ##
##                             ##
#################################
##
#SubRoutine: main
#Description: Opens the files. Returns failure if they cannot be opened
#             Creates a hash table for all of the interval values so that 
#                     input file values can be looked up against the hash
#                     table. Returns failure if there is a problem in creating
#                     the hash table.
#             Determines input file layout based on file name structure
#             Loops through input file. Copies comment lines to tempfile.
#                     Copies appropriate rows with fill value at appropriate
#                     column to tempfile. Copies non-filled rows to tempfile.
#                     Fails on unexpected tokens (not enough columns, 
#                     blank line).
#             Copies temp file to output file
#
#Parameters: $_[0] = pInputFile: The file path/name of the input file
#            $_[1] = pIntervalFile: File path/name of the interval file
#            $_[2] = pTempFile: File path/name of the temporary output file
#            $_[3] = pOutputFile: File path/name of the final output file
#            $_[4] = pUseVerbose: If verbose output should occur
#            $_[5] = pFillValue: The fill value to use
#
#Returns: Undefined if a failure occurs. 1 if successful.
##
sub main {
  ## Variables ##
  my $fillCount = 0; #the number of values filled
  my $curInputLineNum =0; #the current input line number
  my $returnedValue; #value returned from functions
  my @splitInputFileName; #input file name split on$INPUT_NAME_SPLIT_CHARACTER
  my $inputFileType; #the type of input file. Determines column layout.
  my $fillColumn; #the column in the input file to fill
  my $timeColumn; #the column in the input file that holds the day.hour
  my @splitInputLine; #array that holds the input line split by whitespace.
  my %timeToFill; #hash table of values to fill

  #parameters
  my $pInputFile; #the input file             (parameter)
  my $pIntervalFile; #the interval file       (parameter)
  my $pTempFile; #the temp file               (parameter)
  my $pOutputFile; #the final output file     (parameter)
  my $pUseVerbose; #use verbose output or not (parameter)
  my $pFillValue; #the fill value             (parameter)

  ## End Variable Declarations##

  ($pInputFile, $pIntervalFile,$pTempFile,$pOutputFile,$pUseVerbose, 
   $pFillValue) = @_;


  #open files
  $returnedValue = open_files($pInputFile, $pIntervalFile,$pTempFile);
  unless (defined($returnedValue)) {
    print "Unable to open files. Main subroutine cannot continue. \n"
          ."Exiting main()\n" if defined($pUseVerbose);
    return undef();
  }

  #create interval hash table
  $returnedValue = create_hash_from_intervals($pUseVerbose);
   unless (defined($returnedValue)) {
    print "Unable to create interval hash table."
          ."Main subroutine cannot continue without hash table. \n"
          ."Exiting main()\n" if defined($pUseVerbose);
    return undef();
  }
  %timeToFill = %$returnedValue;

  #determine input file column layout
  @splitInputFileName = split($INPUT_NAME_SPLIT_CHARACTER,$pInputFile);
  $inputFileType = $splitInputFileName[$INPUT_FILE_TYPE_COLUMN];
  $fillColumn = $INPUT_COLUMNS{$inputFileType}{"fill"};
  $timeColumn = $INPUT_COLUMNS{$inputFileType}{"time"};
  print "Using $inputFileType file... Fill Column:$fillColumn\n";
  
  
  ###
  ##BEGIN PROCESSING INPUT FILE##
  #loop through input file
  print "Writing to temp file...\n"                     if ($pUseVerbose);

 INPUT_LOOP:  
  while (my $curInputLine = <INPUT_FILE>) {
    $curInputLineNum++;

    #If line is a comment, write it out to temp
    if ($curInputLine =~ /^#/) {
      print TEMP_FILE "$curInputLine";
      print "$curInputLineNum(Comment): $curInputLine"  if ($pUseVerbose);
      next INPUT_LOOP;
    }

    #split line into tokenarray delimited by spaces
    @splitInputLine = split(/\s+/,$curInputLine);

    #if split has not created fill column and time column, then the line
    #is ill formatted. Cannot continue. Exiting.
    unless (defined($splitInputLine[$timeColumn]) 
	    and defined($splitInputLine[$fillColumn])) {
      print TEMP_FILE "$curInputLine";
      print "Unexpected line format at input file line $curInputLineNum.\n";
      print "Unable to continue.\n"                    if ($pUseVerbose);
      print "Current Line($curInputLineNum): $curInputLine" if ($pUseVerbose);
      return undef;
    }

    #if line is in interval,  write out line to temp with fill value
    if (defined($timeToFill{$splitInputLine[$timeColumn]})) {

      #replace the current value with the fill value)
      #if space delimited, add a space to the fill value
      unless ($curInputLine =~ 
	      s/ $splitInputLine[$fillColumn]/$pFillValue/) {

	#if it didn't work (tab or otherwhitespace delimited)
	$curInputLine =~ s/$splitInputLine[$fillColumn]/$pFillValue /;
      }

      #output line to temp file
      print TEMP_FILE "$curInputLine";
      print "$curInputLineNum(FILLED):  $curInputLine"  if ($pUseVerbose);

      #count number filled
      $fillCount ++;
    }
    else {
      #if line is not in interval, write out line to temp as is
      print TEMP_FILE "$curInputLine";
      print "$curInputLineNum(As is):   $curInputLine"  if ($pUseVerbose);

    }
  }
  #writeout number filled
  print "$fillCount values filled.\n";

  #close files
  close INPUT_FILE;
  close INTERVAL_FILE;
  close TEMP_FILE;

  #copy tempfile to output file
  copy($pTempFile,$pOutputFile);

  print "exiting main()\n" if ($pUseVerbose);
  ##success
  return 1;
}

#################################
##                             ##
##        SUB ROUTINES         ##
##                             ##
#################################

##
#SubRoutine: open_files
#Description: Opens the files. Dies if they cannot be opened
#Parameters: @_[0]=OpenInputFile: The file path/name of the input file to open
#            @_[1]=OpenIntervalFile: File path/name of interval file to open
#            @_[2]=OpenTempFile: File path/name oftemporary output file to open
#Returns: (none)
##
sub open_files {

  #Get the parameters
  my ($pOpenInputFile,$pOpenIntervalFile, $pOpenTempFile) = @_;

  #open input file
  unless (open(INPUT_FILE, $pOpenInputFile)) {
    print "Can't open input file ($pOpenInputFile).\n";
    return undef();
  }
 
  #open interval file
  unless (open(INTERVAL_FILE, $pOpenIntervalFile)) {
    print "Can't open interval file ($pOpenIntervalFile).\n";
    return undef();
  }

  #open temp file
  unless (open(TEMP_FILE, ">$pOpenTempFile")){
    print "Can't open temp file ($pOpenTempFile). Exiting...\n";
    return undef();
  }


  #successful completion
  return 1;

}


##
#SubRoutine: create_hash_from_intervals
#Description: Uses the interval file to create a hash table of values to fill
#             All values between start and end (inclusive) are added as hash
#             keys with a value of 1.
#
#Parameters: pUseVerboseHash: true if verbose output should be used here
#
#Returns: hash table reference or undefined if failure
##
sub create_hash_from_intervals {
  my $blnGoodIntervalFile = 1;
  my $intervalLineCount = 0;
  my @fullInterval;
  my @start; #first position is the full day, second is the fraction of day
  my @end;   #same as end
  my $pUseVerboseHash;  #if this should use verbose
  my %allValues;  #all the values between intervals

  ($pUseVerboseHash) = @_;

  print "Creating hash from intervals...\n" if defined($pUseVerboseHash);
  INTERVAL_LINE: 
  while (my $curInputLine = <INTERVAL_FILE>) {
    $intervalLineCount++;  #increment line counter
    #writeout output if verbose is on
    print "Line: $intervalLineCount => $curInputLine"  
                                            if defined($pUseVerboseHash);

    #If line is a comment, skip
    next INTERVAL_LINE if $curInputLine =~ /^#/;

    #if line is a blank line, skip
    next INTERVAL_LINE if $curInputLine eq "\n";

    #if line matches:
    # [1-3 digit number].[digit][digit][whitespace][1-3 digit number].
    # [digit][digit]
    #then it is good. Otherwise, output error
    if ($curInputLine =~ /^\d{1,3}\.\d\d\s+\d{1,3}\.\d\d/) {

      #split line by whitespace and then by decimals
      @fullInterval = split(/\s+/, $curInputLine);
      @start = split(/\./, $fullInterval[0]);
      @end = split(/\./, $fullInterval[1]);

      #make sure that the start value is actually before the end value
      # if not, exit and print error
      if (($start[0] > $end[0]) or ($start[1] > $end[1])) {
	print "Interval File Error (Start value greater than end value)"
	     ."at line: $intervalLineCount\n"
	     ."    $curInputLine\n";
	$blnGoodIntervalFile = undef();
	last INTERVAL_LINE;
      }

      #create hash table that starts at @start, ends at @end (inclusive)
      #iterate by day
      for (my $curDayCount = $start[0];
	      $curDayCount < $end[0]+1;
	      $curDayCount++) {
	#iterate by fraction of day
	for (my $curFractionCount = $start[1];
	        $curFractionCount < $end[1]+1;
	        $curFractionCount++) {
	  #make sure that the curFractionCount has a leading zero if it is
	  #less than 10. Otherwise, the hash will be thrown off
	  if ($curFractionCount < 10) {
	    $curFractionCount = "$curFractionCount";
	  }
	  $allValues{$curDayCount . "." . $curFractionCount} = 1;
	
	  #writeout value if verbose is on
	  print $allValues{$curDayCount . "." . $curFractionCount}
	        .":$curDayCount.$curFractionCount Added\n" 
	        if defined($pUseVerboseHash);
	}
      } #end loop through current start and end
    }  #end good curinputline
    else {
      #error in file. Writeout error and exit loop
      print "Interval File Error (unexpected token) "
	   ."at line: $intervalLineCount\n"
	   ."    $curInputLine\n";

      #find token problem and print it
      if ($curInputLine =~ /^\d{1,3}/) {
	if ($curInputLine =~ /^\d{1,3}\./) {
	  if ($curInputLine =~ /^\d{1,3}\.\d\d/) {
	    if ($curInputLine =~ /^\d{1,3}\.\d\d\s+/) {
	      if ($curInputLine =~ /^\d{1,3}\.\d\d\s+\d{1,3}/) {
		if ($curInputLine =~ /^\d{1,3}\.\d\d\s+\d{1,3}\./) {
		  if ($curInputLine =~ /^\d{1,3}\.\d\d\s+\d{1,3}\.\d\d/){
		  }
		  else {print "end day two-digit fraction day missing\n";}
		}
		else {print "end day decimal point missing\n";}
	      }
	      else {print "end day number invalid\n";}
	    }
	    else {print "whitespace missing between start and end day\n";}
	  }
	  else {print "start day two-digit fraction day missing\n";}
	}
	else {print "start day decimal point missing\n";}
      }
      else {print "Start day number invalid (1-3 digits expected)\n";}

      $blnGoodIntervalFile = undef();
      last INTERVAL_LINE;
    }

  } #end interval_line while

  print "Lines Processed: $intervalLineCount\n"
       ."Exiting create_hash_from_intervals\n\n" 
	 if defined($pUseVerboseHash);

  #Did it succeed? If yes, return hash table. If not, return failure.
  if ($blnGoodIntervalFile) {
    \%allValues;#return hash table
  }
  else { undef();}#return failure 

}
