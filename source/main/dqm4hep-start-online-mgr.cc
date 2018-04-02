/// \file dqm4hep-start-online-mgr.cc
/*
 *
 * dqm4hep-start-online-mgr.cc main source file template automatically generated
 * Creation date : mer. nov. 5 2014
 *
 * This file is part of DQM4HEP libraries.
 *
 * DQM4HEP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 *
 * DQM4HEP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DQM4HEP.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author Remi Ete
 * @copyright CNRS , IPNL
 */

// -- dqm4hep headers
#include "dqm4hep/Internal.h"
#include "dqm4hep/StatusCodes.h"
#include "dqm4hep/Logging.h"
#include "dqm4hep/OnlineManagerServer.h"
#include "DQMOnlineConfig.h"

// -- tclap headers
#include "tclap/CmdLine.h"
#include "tclap/Arg.h"

// -- std headers
#include <iostream>
#include <signal.h>

using namespace std;
using namespace dqm4hep::online;
using namespace dqm4hep::core;

std::shared_ptr<OnlineManagerServer> server;

//-------------------------------------------------------------------------------------------------

// key interrupt signal handling
void int_key_signal_handler(int signal)
{
  std::cout << std::endl;
  dqm_info( "Caught CTRL+C. Stopping server...", signal );

  if(server) {
    server->stop();
  }
}

//-------------------------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
  dqm4hep::core::screenSplash();

  std::string cmdLineFooter = "Please report bug to <dqm4hep@gmail.com>";
  TCLAP::CmdLine *pCommandLine = new TCLAP::CmdLine(cmdLineFooter, ' ', DQMOnline_VERSION_STR);

  StringVector verbosities(Logger::logLevels());
  TCLAP::ValuesConstraint<std::string> verbosityConstraint(verbosities);
  TCLAP::ValueArg<std::string> verbosityArg(
      "v"
      , "verbosity"
      , "The logging verbosity"
      , false
      , "info"
      , &verbosityConstraint);
  pCommandLine->add(verbosityArg);
  
  // parse command line
  pCommandLine->parse(argc, argv);
  
  std::string verbosity(verbosityArg.getValue());
  Logger::setLogLevel(Logger::logLevelFromString(verbosity));

  // install signal handlers
  signal(SIGINT,  int_key_signal_handler);
  
  try
  {
    server = std::make_shared<OnlineManagerServer>();
    server->run();
  }
  catch(StatusCodeException &exception)
  {
    dqm_error( "Caught exception while running: {0}", exception.toString() );
    return exception.getStatusCode();
  }

  return 0;
}
