/*
  File: AmStopMcpPhaFilter.h

  Description:

    Header file for AmStopMcpPhaFilter class.  This filter excludes
    ACE/SWIMS PHAs that do not have sensible position on the stop MCP,
    given PHA energy, m/q, He2+ speed, and hyperbola/fin voltages.

  Author(s): Jim Raines (jmr)

  Method:

  Algorithm and most constants taken from
  getdata5.cpp::get_stop_mcp_pos by Roland Schaerer and Bob Wimmer.

  Revision controlled by CVS:
  $Id: AmStopMcpPhaFilter.h,v 1.1 2004/04/27 20:39:26 jraines Exp $

  Major Modification History:
    17Mar2004   jmr   initial coding

*/

class AmStopMcpPhaFilter : public AmPhaFilter {
 public:

  AmStopMcpPhaFilter();

  AmStopMcpPhaFilter(const InstrumentConstants& ic,
					 const AceSwimsHousekeeping& hk);

  virtual bool passFilter(const AceSwimsPha& pha) const;

  // toggle testing if stop mcp position within range
  void setTestStopPos(bool value);
  bool getTestStopPos();

 private:

  InstrumentConstants IC;
  const AceSwimsHousekeeping* HK;

  // toggle testing if stop mcp position within range
  bool testStopPos;

};
