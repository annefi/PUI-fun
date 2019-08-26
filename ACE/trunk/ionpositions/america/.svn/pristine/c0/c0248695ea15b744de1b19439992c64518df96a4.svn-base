#! /usr/bin/perl
#
# File:  axlv2_deliv_adjust.pl
#
# Description:
#   Methods for filling a file's particular column within a given number of
#   rows with a fill value. For example, in an Iron charge distribution file,
#   the relative abundance column is filled with the default fill value 
#   from time 183.08 to time 183.09.
#
#   Basic functionality: 
#     (1)reads input file defined by --input_file option,
#     (2)reads interval file (fill_interval.txt) 
#     (3)writes changes line by line to a temp file in the temp directory
#     (3)copies the tempfile to '[inputfile].adjusted'
#
#   -The fill value can be defined (NVT usually needs a shorter fill val)
#   -All values in a column *can* be scaled if requested
#
#  Input File Format: Varies. # = comment and the time and fill columns
#                      are defined below. Columns are separated by spaces
#
#  Interval File Format:
#  # <-- Comment at beginning of line
#  123.01  123.34   (1,2)<-- 1-3 digit number, decimal point, 2 digit number, 
#                            spaces, repeat once. open paren, whole number, 
#                            comma, repeat as necessary
#                             First number is the start point (inclusive)
#                             Second number is the end point (inclusive)
#                             Parentheses specify fill columns. This is
#                                 optional. 1 or multiple, comma-separated vals
#                                 can be used. -1 means use default.
#
# Author(s):  Nick Montgomery (ndm)
#
# Methods/Subroutines:
#         main
#         open_files
#         create_hash_from_intervals
#         replace_portion_of_line
#
# Revision controlled by CVS:
#
#
# Major Modification History:
#
#
#$DB::single=2; #debugging breakpoint

##############
# perl setup #
##############
use strict;
use warnings;
use Getopt::Long;
use File::Copy;
our $thisPackage = "axlv2_deliv_adjust";

#######################
# ===> configure <=== #
#######################\
### PSEUDO CONSTANTS###
#Defaults
my $DEFAULT_TEMP_FILE = "$thisPackage.tempfile." . time();
my $DEFAULT_INTERVAL_FILE = "fill_intervals.txt";
my $DEFAULT_OUTPUT_FILE_EXTENSION = ".adjusted";
my $DEFAULT_FILL_VALUE = "-1.00e+00"; #the code below expects a negative num

#positions in the interval file
my $INTERVAL_START_POS = 0;
my $INTERVAL_END_POS   = 1;
my $INTERVAL_FILL_POS  = 2;

my $USE_DEFAULT_FILL_COLS = -1;

#input file split character
my $INPUT_NAME_SPLIT_CHARACTER = "_";

# location to store temporary files
# typical: "/tmp"
my $TEMP_DIR = "/tmp";

#hash keys
my $KEY_FILL = "fill";
my $KEY_TIME = "time";
my $KEY_SCALAR  = "nHe2";

#scalar comment line
#$1 = comment description
#$2 = parentheticals
#$3 = existing scale
#$4 = decimal portion
my $REGEXP_SCALAR_COMMENT = '^(# Data version: \d+\.\d+)( \((\d+(\.\d+)?)\))?';

#input file types hash table (stores the fill and time column numbers)
my %INPUT_COLUMNS = (
			"qdist"  => {$KEY_FILL  => [4],
				     $KEY_TIME  => 1,},

		        "nvt"    => {$KEY_FILL  => [2,3,4,6,7,9,10,12,13,15],
				     $KEY_TIME  => 1,
				     $KEY_SCALAR => 2,},

		        "elem"   => {$KEY_FILL  => [2,4,6,8,10,12],
				     $KEY_TIME  => 1,},

		        "qratio" => {$KEY_FILL  => [2,4,6,8,10],
				     $KEY_TIME  => 1,},
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
    $useVerbose, $fillValue, $noFill, $nHeScalar);
#Declare argument variables as local
my ($argInputFile, $argIntervalFile, $argReuseInput, 
    $argOutputFile, $argTempFile, $argVerbose, $argFillValue, $argNoFill,
    $argNHeScalar, $argHelp);

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
."--no_fill          Use if you do not want to fill values (use w/ scalar)"
."--nhe_scalar     = [Float nHe scale value]"
."--verbose          Use if you wan't verbose output\n\n"
."--help             Use to display this help screen\n"
."\n\n";

GetOptions("input_file=s"   => \$argInputFile,
	  "interval_file=s" => \$argIntervalFile,
	  "reuse_input"     => \$argReuseInput,
	  "output_file=s"   => \$argOutputFile,
	  "temp_file=s"     => \$argTempFile,
	  "fill_value=s"    => \$argFillValue,
          "no_fill"         => \$argNoFill,
          "nhe_scalar=s"    => \$argNHeScalar,
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

#no_fill
if (defined($argNoFill)) {$noFill = $argNoFill;}
else {$noFill = undef();}

#nHe Scalar
if (defined($argNHeScalar)) {$nHeScalar = $argNHeScalar;}
else {$nHeScalar = undef();}

#verbose
if (defined($argVerbose)) {$useVerbose = 1;}
else {$useVerbose=undef();}

#writeout command line options that user inputted
print "\nRunning Program: $thisPackage\n"
     ."InputFile:       $inputFile\n"
     ."IntervalFile:    $intervalFile\n"
     ."TempFile:        $tempFile\n"
     ."OutputFile:      $outputFile\n"
     ."FillValue:       $fillValue\n";
print "Not filling values\n"             if defined($noFill);
print "nHe Scalar:      $nHeScalar\n"    if defined($nHeScalar);
print "Using Verbose Output"             if defined($useVerbose);
print "\n\n\n";


#Run main program
if (main ($inputFile, $intervalFile, $tempFile, $outputFile, $useVerbose, 
	  $fillValue, $noFill, $nHeScalar)) {
  print "Exiting following successful completion.\n";
  #Exit with no errors
  exit(0);
}
else {die "Exiting following failure!!\n";}


##########################
#> End Inline Commands  <#
##########################



#################################
##                             ##
##        MAIN FUNCTION        ##
##                             ##
#################################
##-----------------------------------------------------------------------------
#SubRoutine: main
#Description:
#             Opens the files. Returns failure if they cannot be opened
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
#Parameters: 
#            $_[0] = pInputFile: The file path/name of the input file
#            $_[1] = pIntervalFile: File path/name of the interval file
#            $_[2] = pTempFile: File path/name of the temporary output file
#            $_[3] = pOutputFile: File path/name of the final output file
#            $_[4] = pUseVerbose: If verbose output should occur
#            $_[5] = pFillValue: The fill value to use
#            $_[6] = pNoFill: Whether to fill or not
#            $_[7] = pNHeScalar: Value to scale by (undef if not at all)
#
#Returns:
#            Undefined if a failure occurs. 1 if successful.
##-----------------------------------------------------------------------------
sub main {
  ## Variables ##
  my $fillCount = 0; #the number of values filled
  my $filledRows = 0; #the number of rows with filled values
  my $scaledRowCount = 0; #the number of rows with scaled values
  my $curInputLineNum =0; #the current input line number
  my $returnedValue; #value returned from functions
  my @splitInputFileName; #input file name split on$INPUT_NAME_SPLIT_CHARACTER
  my $inputFileType; #the type of input file. Determines column layout.
  my $fillColumnsRef; #the reference to the column for filling array
  my @defFillColumns; #array of default columns to fill
  my @fillColumns; #array of the actual columns to fill
  my $timeColumn; #the column in the input file that holds the day.hour
  my $scaleColumn; #the column in the input file that should be scaled
  my @splitInputLine; #array that holds the input line split by whitespace.
  my %timeToFill; #hash table of values to fill
  my $inputFileNoPath; #the input file without any directories
  my $blnScaled;  #defined if the row was scaled
  #my $regexpToKeep;#the portion of the input line that should not be replaced
  #my $strToKeep;
  #my $regexpToReplace;
  #my $fillLengthDiff; #difference in length between existing and fill values

  #parameters
  my $pInputFile; #the input file             (parameter)
  my $pIntervalFile; #the interval file       (parameter)
  my $pTempFile;  #the temp file              (parameter)
  my $pOutputFile;#the final output file      (parameter)
  my $pUseVerbose;#use verbose output or not  (parameter)
  my $pFillValue; #the fill value             (parameter)
  my $pNoFill;    #to fill or not to fill?    (parameter)
  my $pNHeScalar; #scale value for nHe2       (parameter)

  ## End Variable Declarations##

  ($pInputFile, $pIntervalFile,$pTempFile,$pOutputFile,$pUseVerbose, 
   $pFillValue, $pNoFill, $pNHeScalar) = @_;

  #////////////////////////////////////////////////////////////////
  #/ START: OPEN FILES
  $returnedValue = open_files($pInputFile, $pIntervalFile,$pTempFile);
  unless (defined($returnedValue)) {
    print "Unable to open files. Main subroutine cannot continue. \n"
          ."Exiting main()\n" if defined($pUseVerbose);
    return undef();
  }
  #/ END Open Files
  #//////////////////////////////////////////////////////////////



  #//////////////////////////////////////////////////////////////
  #/ START: GET INTERVALS
  #create interval hash table
  unless (defined($pNoFill)) {
    $returnedValue = create_hash_from_intervals($pUseVerbose);
    unless (defined($returnedValue)) {
      print "Unable to create interval hash table."
	."Main subroutine cannot continue without hash table. \n"
          ."Exiting main()\n" if defined($pUseVerbose);
      return undef();
    }
    %timeToFill = %$returnedValue;
  }
  #/ END Get Intervals
  #///////////////////////////////////////////////////////////////



  #//////////////////////////////////////////////////////////////
  #/ START: GET FILE TYPE 

  #(remove any directories from input filename in order to do this)
  $inputFileNoPath = $pInputFile;
  $inputFileNoPath =~ s/.*\///;
  @splitInputFileName = split($INPUT_NAME_SPLIT_CHARACTER,$inputFileNoPath);

  #search through the filename array to find the type of file (the position
  #changes)
  $inputFileType = undef();
 FILE_TYPE_TOKEN_LOOP:
  foreach my $fileNameToken (@splitInputFileName) {
    next FILE_TYPE_TOKEN_LOOP unless defined($INPUT_COLUMNS{$fileNameToken});
    $inputFileType = $fileNameToken;
  }

  unless (defined($inputFileType)) {
    print "Unknown File Type!.";
    print "Main subroutine cannot continue without known filetype. \n"
          ."Exiting main()\n" if defined($pUseVerbose);
    return undef();
  }
  print "Using $inputFileType file...";

  $fillColumnsRef = $INPUT_COLUMNS{$inputFileType}{$KEY_FILL};
  @defFillColumns = @$fillColumnsRef; #dereference array
  print "Default fill columns: ";

  foreach my $fillColumn (@defFillColumns) { print "$fillColumn,"; }
  print "\n\n";

  $timeColumn = $INPUT_COLUMNS{$inputFileType}{$KEY_TIME};

  #scale column
  if (defined($pNHeScalar)) {
    print "Column to scale: ";
    if (defined($INPUT_COLUMNS{$inputFileType}{$KEY_SCALAR})) {
      $scaleColumn = $INPUT_COLUMNS{$inputFileType}{$KEY_SCALAR};
      print "$scaleColumn\n"
    }
    else {
      print "Not defined for $inputFileType filetype!\n";
      print "Main subroutine cannot continue without column to scale. \n"
          ."Exiting main()\n" if defined($pUseVerbose);
      return undef();
    }
  }


  #/ END Get File type
  #//////////////////////////////////////////////////////////////



  #/////////////////////////////////////////////////////////////
  ##BEGIN PROCESSING INPUT FILE##
  #loop through input file
  print "Writing to temp file...\n"                     if ($pUseVerbose);

 INPUT_LOOP:  
  while (my $curInputLine = <INPUT_FILE>) {
    $curInputLineNum++;

    ##=== COMMENT LINE ===##
    #If line is a comment, write it out to temp
    #  if scaling, write appropriate scale value
    #     if scale value already exists, multiply by new one
    #     else write new one
    if ($curInputLine =~ /^#/) {
      if (defined($pNHeScalar) && ($curInputLine =~ $REGEXP_SCALAR_COMMENT)) {
	if (defined($2)) {
	  my $newScalar;
	  $newScalar = $3*$pNHeScalar;
	  #$newScalar = sprintf("%.2f",$newScalar); #ensure 2 decimals
	  $curInputLine = "$1 ($newScalar)\n";
	  print "Old Scalar: $3 New Scalar: $newScalar" if ($pUseVerbose);
	}
	else {
	  $curInputLine = "$1 ($pNHeScalar)\n";
	  print "New Scalar: $pNHeScalar"               if ($pUseVerbose);
	}
      }
      print TEMP_FILE "$curInputLine";
      print "$curInputLineNum(Comment): $curInputLine"  if ($pUseVerbose);
      next INPUT_LOOP;
    }
    ##== END COMMENT LINE ==##


    ##===  REGULAR LINE  ===##
    #split line into tokenarray delimited by spaces
    @splitInputLine = split(/\s+/,$curInputLine);

    #if split has not created time column, then the line
    #is ill formatted. Cannot continue. Exiting.
    unless (defined($splitInputLine[$timeColumn])) {
      print "Unexpected line format (unable to find time column $timeColumn)"
	   ."at input file line $curInputLineNum.\n";
      print "Unable to continue.\n"                        if ($pUseVerbose);
      print "Current Line($curInputLineNum): $curInputLine"if ($pUseVerbose);
      return undef;
    }

    #----- SCALE -----#
    if (defined($pNHeScalar)) {
      if (defined($splitInputLine[$scaleColumn])) {
	my $scaledValue = $splitInputLine[$scaleColumn] * $pNHeScalar;
	$scaledValue = sprintf("%.2e", $scaledValue); #scientific notation
	#call function that replaces the old value with the new
	$returnedValue = replace_portion_of_line($scaleColumn, $scaledValue,
						 $curInputLine, 
						 \@splitInputLine,
						 $pUseVerbose);
	if (defined($returnedValue)) {$curInputLine = $returnedValue;}
	else {
	  print "Input file line: $curInputLineNum\n";
	  print "Unable to scale at input file line $curInputLineNum.\n"
	       ."Main subroutine will not continue. \n"
               ."Exiting main()\n" if defined($pUseVerbose);
	  return undef();
	}
	$blnScaled = 1;
	$scaledRowCount ++;
      }
      else {$blnScaled = undef();}
    }



    #----- FILL -----#
    #if line is in interval,  write out line to temp with fill value
    if (defined($timeToFill{$splitInputLine[$timeColumn]})) {

      #if not filling, don't worry about the fill logic
      unless (defined($pNoFill)) {

	#did user specify fill columns?
	if ($timeToFill{$splitInputLine[$timeColumn]}[0]
	    == $USE_DEFAULT_FILL_COLS) {
	  @fillColumns = @defFillColumns;
	} else {
	  @fillColumns = @{$timeToFill{$splitInputLine[$timeColumn]}};
	}

	#loop through all fill columns
      FILL_LOOP:
	foreach my $fillColumn (@fillColumns) {	

	  #if previous split has not created fill column, then the line
	  #is ill formatted. Cannot continue. Exiting.
	  unless (defined($splitInputLine[$fillColumn])) {
	    print "Unexpected line format (unable to find fill column "
	      ."$fillColumn) at input file line $curInputLineNum.\n";
	    print "Unable to continue.\n"                   if ($pUseVerbose);
	    print "Current Line($curInputLineNum): $curInputLine"
	      if ($pUseVerbose);
	    return undef;
	  }

	  #call function that replaces the old value with the new
	  $returnedValue = replace_portion_of_line($fillColumn, $pFillValue,
						   $curInputLine, 
						   \@splitInputLine,
						   $pUseVerbose);
	  if (defined($returnedValue)) {$curInputLine = $returnedValue;}
	  else {
	    print "Input file line: $curInputLineNum\n";
	    print "Unable to fill at input file line $curInputLineNum.\n"
	      ."Main subroutine will not continue. \n"
		."Exiting main()\n" if defined($pUseVerbose);
	    return undef();
	  }
	  $fillCount ++;
	}			#end fill column loop
      }                      #end unless $pNoFill

      #output line to temp file
      print TEMP_FILE "$curInputLine";
      print "$curInputLineNum(FILLED):  $curInputLine"  if ($pUseVerbose);

      #count number of rows with filled values
      $filledRows ++;
    }
    ##== END REGULAR LINE ==##


    ##==== UNUSED LINE ====##
    else {
      #if line is not in interval, write out line to temp as is 
      #(it may have been scaled)
      print TEMP_FILE "$curInputLine";
      if ($pUseVerbose) {
	if ($blnScaled) {print "$curInputLineNum(Scaled):   $curInputLine";}
	else {print "$curInputLineNum(As is):   $curInputLine";}
      }
    }
    ##== END UNUSED LINE  ==##

  } #end input while


  #writeout number filled
  print "$fillCount values filled on $filledRows rows.\n";
  print "$scaledRowCount rows scaled\n"       if (defined($pNHeScalar));
  #/ END Processing Input File
  #/////////////////////////////////////////////////////////////



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

##-----------------------------------------------------------------------------
# SubRoutine:
#             open_files
# Description:
#             Opens the files. Dies if they cannot be opened
# Parameters: 
#             @_[0]=OpenInputFile: The file path/name of the input file to open
#             @_[1]=OpenIntervalFile: File path/name of interval file to open
#             @_[2]=OpenTempFile: File path/name oftemporary output file toopen
# Returns:
#             (none)
##-----------------------------------------------------------------------------
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


##-----------------------------------------------------------------------------
# SubRoutine: create_hash_from_intervals
# Description: 
#             Uses the interval file to create a hash table of values to fill
#             All values between start and end (inclusive) are added as hash
#             keys with a value of 1.
#
# Parameters:
#             $_[0] = pUseVerboseHash: true if verbose output should be used
#
# Returns:
#             hash table reference or undefined if failure
##-----------------------------------------------------------------------------
sub create_hash_from_intervals {
  my $blnGoodIntervalFile = 1;
  my $intervalLineCount = 0;
  my @timeExistsValue;
  my @fillColumns;
  my @fullInterval;
  my @start; #first position is the full day, second is the fraction of day
  my @end;   #same as end
  my $pUseVerboseHash;  #if this should use verbose
  my %allValues;  #all the values between intervals
  my $startFraction; #this holds the fraction of day at which the inner loop
                     #should start. It is used for situations that span
                     #multiple days  and need the start fraction to be 0 after
                     # the first day
  my $endFraction; #this holds the fraction of day at which the inner loop
                   #should end. It is used for situations that span multiple
                   #days and need the fraction to go from start to 99, then
                   #start over again

  ($pUseVerboseHash) = @_;

  print "Creating hash from intervals...\n"      if defined($pUseVerboseHash);
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
      @start = split(/\./, $fullInterval[$INTERVAL_START_POS]);
      @end = split(/\./, $fullInterval[$INTERVAL_END_POS]);

      #make sure that the start value is actually before the end value
      #(start-day > end-day) 
      #or (start-day and end-day equal, but start-hour > end-hour)
      # if not, exit and print error
      if (($start[0] > $end[0]) 
	  or (($start[0] == $end[0]) and ($start[1] > $end[1]))) {
	print "Interval File Error (Start value greater than end value)"
	     ."at line: $intervalLineCount\n"
	     ."    $curInputLine\n";
	$blnGoodIntervalFile = undef();
	last INTERVAL_LINE;
      }


      #check to see if the fill columns are specified
      if (defined($fullInterval[$INTERVAL_FILL_POS])) {

	#only positive whole numbers are accepted, or the default value
	if (($fullInterval[$INTERVAL_FILL_POS] =~ /^\((\d+(,\d+)*)\)$/) 
	    or ($fullInterval[$INTERVAL_FILL_POS] =~ /^\(($USE_DEFAULT_FILL_COLS)\)$/)) {
	  @fillColumns = split(/,/,$1);
	  @timeExistsValue = (@fillColumns);
	  print "User specified fill columns:"   if defined($pUseVerboseHash);
	  foreach my $fillColumn (@fillColumns) {
	    print "$fillColumn,"                 if defined($pUseVerboseHash);
	  }
	  print "\n"                             if defined($pUseVerboseHash);
	}
	else {
	  print "Interval File Error (invalid fill column specified)"
	       ."at line: $intervalLineCount\n"
	       ."    $curInputLine\n";
	  $blnGoodIntervalFile = undef();
	  last INTERVAL_LINE;
	}
	
      }
      else { @timeExistsValue = ($USE_DEFAULT_FILL_COLS);  }



      #create hash table that starts at @start, ends at @end (inclusive)
      #iterate by day
      for (my $curDayCount = $start[0];
	      $curDayCount < $end[0]+1;
	      $curDayCount++) {
	
	#set start and end  point appropriately for intervals that span 
	#multiple days
	if ($curDayCount == $start[0]) {$startFraction = $start[1];}
	else {$startFraction = '00';}

	if ($curDayCount == $end[0]) {$endFraction = $end[1];}
	else {$endFraction = 99;}

	#iterate by fraction of day, include end point
	for (my $curFractionCount = $startFraction;
	        $curFractionCount < $endFraction+1;
	        $curFractionCount++) {
	  #make sure that the curFractionCount has a leading zero if it is
	  #less than 10. Otherwise, the hash will be thrown off
	  if ($curFractionCount < 10) {
	    $curFractionCount = "$curFractionCount";
	  }

	  #Set values in hash table
	  $allValues{$curDayCount . "." . $curFractionCount} = [@timeExistsValue];
	
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




##-----------------------------------------------------------------------------
# SubRoutine:  replace_portion_of_line
# Description: 
#             replaces the specific portion of a line
#
# Parameters:  
#             $_[0] = pReplaceColumn: The column to replace
#             $_[1] = pNewValue: The new value
#             $_[2] = pLine: The input line
#             $_[3] = pSplitLineRef: reference to the input line array 
#                            (the orig will be modified)
#             $_[4] = pUseVerboseReplace: verbose output (defined/undef)
#
# Returns:    line with specified portion replaced
##-----------------------------------------------------------------------------
sub replace_portion_of_line {

  my $strToKeep;
  my $regexpToReplace;
  my $regexpToKeep;
  my $fillLengthDiff;

  #Get Parameters
  my ($pReplaceColumn, $pNewValue, $pLine, $pSplitLineRef, 
      $pUseVerboseReplace) = @_;

  #make sure variables exist
  unless (defined($pReplaceColumn) && defined($pNewValue) 
	  && defined($pLine) && defined($pSplitLineRef)) {
    print "Error: Parameters missing in method replace_portion_of_line\n";
    return undef();
  }


  #format the search value for reg expressions. In order to ensure that
  #the correct column is replaced (there could be two 3.0e+01s), add
  #the beginning of the entire string to the regexp
  #this portion of the code slows down the program significantly
  $regexpToKeep = '^\s*';
  for (my $countCol = 1; $countCol < $pReplaceColumn; $countCol++) {
    $strToKeep = $$pSplitLineRef[$countCol];
    $strToKeep =~ s/\+/\\\+/; #format the exponent symbol
    $strToKeep =~ s/\./\\\./; #format the decimal point
    $regexpToKeep .= $strToKeep .'\s+';
  }
  $regexpToReplace = $$pSplitLineRef[$pReplaceColumn];
  $regexpToReplace =~ s/\./\\\./; #format the decimal point
  $regexpToReplace =~ s/\+/\\\+/; #format the exponent symbol
	
  $pLine =~ /($regexpToKeep)/;
  $strToKeep = $1;

  #replace the current value with the fill value)
  #if space delimited, add a space to the fill value where necessary
  #if the existing number and the fill value are the same length, we
  #do not need to worry about whitespace. 
  #If existing is <>, we need to make sure that the output has
  #the correct formatting
  $fillLengthDiff = length("$$pSplitLineRef[$pReplaceColumn]") -
    length("$pNewValue");
 SWITCH: {
    ##CASE: Same length
    if ($fillLengthDiff == 0) {
      $pLine =~ s/$regexpToKeep$regexpToReplace/$strToKeep$pNewValue/;
      $$pSplitLineRef[$pReplaceColumn] = $pNewValue;
      last SWITCH;
    }

    ##CASE: Fill is longer
    if ($fillLengthDiff < 0) {
      my $spaces = " " x (1-$fillLengthDiff);
      #is there enough space (at least one +) before the fill column?
      if ($pLine =~ /$spaces$regexpToReplace/) {
	$spaces = " " x (0-$fillLengthDiff);
	$pLine =~ s/$spaces$regexpToReplace/$pNewValue/;
	$$pSplitLineRef[$pReplaceColumn] = $pNewValue;
      } else {		#not enough space. Exit!
	print "Not enough space for new value $pNewValue. Existing: "
	     ."$$pSplitLineRef[$pReplaceColumn]\n";
	print "Unable to continue.\n"               if ($pUseVerboseReplace);
	return undef();
      }
      last SWITCH;
    }

    ##CASE: Fill is shorter
    if ($fillLengthDiff > 0) {
      my $spaces = " " x ($fillLengthDiff);
      $pLine =~ s/$regexpToReplace/$spaces$pNewValue/;
      $$pSplitLineRef[$pReplaceColumn] = $pNewValue;
      last SWITCH;
    }

  }

  return $pLine;
}

# enables inclusion in other code by require
1;