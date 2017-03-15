  /// \file RunControlInterface.cc
/*
 *
 * RunControlInterface.cc source template automatically generated by a class generator
 * Creation date : mar. janv. 24 2017
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
 * @author Remi ete
 * @copyright CNRS , IPNL
 */

// -- dqm4hep headers
#include "dqm4hep/RunControlInterface.h"
#include "dqm4hep/RunControl.h"
#include "dqm4hep/Run.h"
#include "dqm4hep/Logging.h"
#include "dqm4hep/CoreTool.h"
#include "dqm4hep/Plugin.h"

// -- std headers
#include <fstream>

#ifdef DQM4HEP_USE_MONGOOSE
#include <mongoose/WebController.h>
#include <mongoose/Server.h>
using namespace Mongoose;
#endif

namespace dqm4hep {

  namespace core {

    RunControlInterface::RunControlInterface() :
      m_pRunControl(nullptr)
    {
      /* nop */
    }

    //-------------------------------------------------------------------------------------------------

    RunControlInterface::~RunControlInterface()
    {
      /* nop */
    }

    //-------------------------------------------------------------------------------------------------

    const RunControl *RunControlInterface::runControl() const
    {
      return m_pRunControl;
    }

    //-------------------------------------------------------------------------------------------------

    void RunControlInterface::startNewRun(const Run &run)
    {
      if(nullptr != m_pRunControl)
        m_pRunControl->startNewRun(run);
    }

    //-------------------------------------------------------------------------------------------------

    void RunControlInterface::endCurrentRun()
    {
      if(nullptr != m_pRunControl)
        m_pRunControl->endCurrentRun();
    }

    //-------------------------------------------------------------------------------------------------

    void RunControlInterface::setRunControl(RunControl *pRunControl)
    {
      m_pRunControl = pRunControl;
    }

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

#ifdef DQM4HEP_USE_MONGOOSE
    class HttpRunControl : public Mongoose::WebController, public RunControlInterface
    {
    public:
      HttpRunControl();

    private:
      void setup();
      /// call back methods on http request
      void mongooseStartOfRunGetForm(Mongoose::Request &request, Mongoose::StreamResponse &response);
      void mongooseEndCurrentRunGetForm(Mongoose::Request &request, Mongoose::StreamResponse &response);
      void mongooseStartOfRun(Mongoose::Request &request, Mongoose::StreamResponse &response);
      void mongooseEndOfRun(Mongoose::Request &request, Mongoose::StreamResponse &response);
      void mongooseRunStatus(Mongoose::Request &request, Mongoose::StreamResponse &response);

      std::string configureRunStatusHtml(const Run &run, bool running) const;

      // from RunControlInterface
      void onServerStartup();
      void onServerShutdown();
      StatusCode readSettings(const ParameterMap &parameters);

    private:
      int                     m_httpPort;
      Mongoose::Server       *m_pMongooseServer;
    };

    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------

    HttpRunControl::HttpRunControl() :
      m_httpPort(8090),
      m_pMongooseServer(nullptr)
    {
      /* nop */
    }

    //-------------------------------------------------------------------------------------------------

    StatusCode HttpRunControl::readSettings(const ParameterMap &parameters)
    {
      auto iter = parameters.find("http-port");

      if(iter != parameters.end())
      {
        if(!DQM4HEP::stringToType(iter->second, m_httpPort))
          return STATUS_CODE_FAILURE;
      }

      return STATUS_CODE_SUCCESS;
    }

    //-------------------------------------------------------------------------------------------------

    void HttpRunControl::onServerStartup()
    {
      m_pMongooseServer = new Mongoose::Server(m_httpPort);
      m_pMongooseServer->registerController( this );
      m_pMongooseServer->start();
      this->dumpRoutes();
    }

    //-------------------------------------------------------------------------------------------------

    void HttpRunControl::onServerShutdown()
    {
      m_pMongooseServer->stop();
    }

    //-------------------------------------------------------------------------------------------------

    void HttpRunControl::setup()
    {
      const std::string &runControlName(this->runControl()->name());

      addRoute( "GET"  , "/" + runControlName + "/SOR" ,     HttpRunControl , mongooseStartOfRunGetForm );
      addRoute( "POST" , "/" + runControlName + "/SOR" ,     HttpRunControl , mongooseStartOfRun );
      addRoute( "GET"  , "/" + runControlName + "/EOR" ,     HttpRunControl , mongooseEndCurrentRunGetForm );
      addRoute( "POST" , "/" + runControlName + "/EOR" ,     HttpRunControl , mongooseEndOfRun );
      addRoute( "GET"  , "/" + runControlName + "/STATUS" ,  HttpRunControl , mongooseRunStatus );
    }

    //-------------------------------------------------------------------------------------------------

    void HttpRunControl::mongooseStartOfRunGetForm(Mongoose::Request &request, Mongoose::StreamResponse &response)
    {
      const std::string &runControlName(this->runControl()->name());

      LOG4CXX_DEBUG( dqmMainLogger , "Received GET: /" + runControlName + "/SOR" );

      if( RUNNING_STATE == this->runControl()->runState() )
      {
        const Run run(this->runControl()->run());
        response << this->configureRunStatusHtml(run, true);
        return;
      }

      std::string fileName = std::string(DQMCore_DIR) + "/web/run-ctrl-sor-form.html";
      std::ifstream in(fileName.c_str(), std::ios::in);
      std::string contents;

      if ( in )
      {
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();

        DQM4HEP::replace( contents , "RUN_CONTROL_NAME" , runControlName );
      }
      else
        contents = "Problem !!";

      response << contents;
    }

    //-------------------------------------------------------------------------------------------------

    void HttpRunControl::mongooseEndCurrentRunGetForm(Mongoose::Request &request, Mongoose::StreamResponse &response)
    {
      const std::string &runControlName(this->runControl()->name());

      LOG4CXX_DEBUG( dqmMainLogger , "Received GET: /" + runControlName + "/EOR" );

      if( RUNNING_STATE != this->runControl()->runState() )
      {
        const Run run(this->runControl()->run());
        response << this->configureRunStatusHtml(run, false);
        return;
      }

      std::string fileName = std::string(DQMCore_DIR) + "/web/run-ctrl-eor-form.html";
      std::ifstream in(fileName.c_str(), std::ios::in);
      std::string contents;

      if ( in )
      {
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();

        DQM4HEP::replace( contents , "RUN_CONTROL_NAME" , runControlName );
      }
      else
        contents = "Problem !!";

      response << contents;
    }

    //-------------------------------------------------------------------------------------------------

    void HttpRunControl::mongooseStartOfRun(Mongoose::Request &request, Mongoose::StreamResponse &response)
    {
      const std::string &runControlName(this->runControl()->name());

      LOG4CXX_DEBUG( dqmMainLogger , "Received POST: /" + runControlName + "/SOR" );

      std::map<std::string, std::string> variables(request.getAllVariable());
      std::map<std::string, std::string> urlVariables;
      request.getVars(urlVariables);

      Run run;
      bool consistent = false;

      for(auto iter = variables.begin(), endIter = variables.end() ; endIter != iter ; ++iter)
      {
        if( iter->first == "run" )
        {
          int runNumber = 0;
          DQM4HEP::stringToType( iter->second , runNumber );
          run.setRunNumber( runNumber );
          consistent = true;
          continue;
        }

        if( iter->first == "description" )
        {
          run.setDescription( iter->second );
          continue;
        }

        if( iter->first == "detectorName" )
        {
          run.setDetectorName( iter->second );
          continue;
        }

        run.setParameter( iter->first , iter->second );
      }

      if( ! consistent )
      {
        response << "ERROR: Run number required to start a new run !!<br/>"<< std::endl;
        return;
      }

      try
      {
        this->startNewRun(run);
      }
      catch( StatusCodeException &exception )
      {
        response << "Couldn't start new run ! What :" << exception.toString()<< std::endl;
        return;
      }

      response << this->configureRunStatusHtml(run, true);
    }

    //-------------------------------------------------------------------------------------------------

    void HttpRunControl::mongooseEndOfRun(Mongoose::Request &request, Mongoose::StreamResponse &response)
    {
      const std::string &runControlName(this->runControl()->name());

      LOG4CXX_DEBUG( dqmMainLogger , "Received POST: /" + runControlName + "/EOR" );

      if( RUNNING_STATE != this->runControl()->runState() )
      {
        // return run status (not running)
        const Run run(this->runControl()->run());
        response << this->configureRunStatusHtml(run, false);
        return;
      }

      std::map<std::string, std::string> variables(request.getAllVariable());

      Run run(this->runControl()->run());
      int runNumber = run.runNumber();

      for(auto iter = variables.begin(), endIter = variables.end() ; endIter != iter ; ++iter)
        run.setParameter( iter->first , iter->second );

      try
      {
        this->endCurrentRun();
      }
      catch( StatusCodeException &exception )
      {
        response << "Couldn't stop current run ! What :" << exception.toString()<< std::endl;
        return;
      }

      response << this->configureRunStatusHtml(run, false);
    }

    //-------------------------------------------------------------------------------------------------

    void HttpRunControl::mongooseRunStatus(Mongoose::Request &request, Mongoose::StreamResponse &response)
    {
      LOG4CXX_DEBUG( dqmMainLogger , "Received GET: /" + this->runControl()->name() + "/STATUS" );

      bool running(this->runControl()->runState() == RUNNING_STATE);
      const Run run(this->runControl()->run());
      response << this->configureRunStatusHtml(run, running);
      return;
    }

    //-------------------------------------------------------------------------------------------------

    std::string HttpRunControl::configureRunStatusHtml(const Run &run, bool running) const
    {
      std::string fileName = std::string(DQMCore_DIR) + "/web/run-ctrl-status.html";
      std::ifstream in(fileName.c_str(), std::ios::in);
      std::string contents;

      if ( in )
      {
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();

        StringVector parameterKeys;
        std::string startTime, elapsedTime, description, detectorName;
        std::string status, statusColor;
        int runNumber;

        if( running )
        {
          parameterKeys = run.parameterKeys();
          CoreTool::timeToHMS( std::chrono::system_clock::to_time_t(run.startTime()), startTime );
          CoreTool::timeToHMS( time(0) - std::chrono::system_clock::to_time_t(run.startTime()), elapsedTime );

          runNumber = run.runNumber();
          description = run.description();
          detectorName = run.detectorName();
          status = "RUNNING";
          statusColor = "green";
        }
        else
        {
          startTime = "-";
          elapsedTime = "-";
          runNumber = 0;
          description = "-";
          detectorName = "-";
          status = "NOT RUNNING";
          statusColor = "red";
        }

        DQM4HEP::replace( contents , "RUN_NUMBER", runNumber );
        DQM4HEP::replace( contents , "START_TIME", startTime );
        DQM4HEP::replace( contents , "ELLAPSED_TIME", elapsedTime );
        DQM4HEP::replace( contents , "DESCRIPTION", description );
        DQM4HEP::replace( contents , "DETECTOR_NAME", detectorName );

        DQM4HEP::replace( contents , "RUN_STATUS", status );
        DQM4HEP::replace( contents , "STATUS_COLOR", statusColor );

        DQM4HEP::replace( contents , "RUN_CONTROL_NAME" , this->runControl()->name() );

        std::string javascriptParameters = "{";

        for( auto iter = parameterKeys.begin(), endIter = parameterKeys.end() ;
            endIter != iter ; ++iter)
        {
          std::string jsParameter("'${KEY}' : '${VALUE}'");

          std::string parameter;
          run.parameter( *iter , parameter );

          DQM4HEP::replace( jsParameter , "KEY" , *iter );
          DQM4HEP::replace( jsParameter , "VALUE" , parameter );

          std::string coma = ( iter == parameterKeys.begin() ) ? "" : " , ";

          javascriptParameters += (coma + jsParameter);
        }

        javascriptParameters += " }";

        DQM4HEP::replace( contents , "PARAMETER_LIST", javascriptParameters );

        return contents;
      }

      return "Invalid operation on server side";
    }

    DQM_PLUGIN_DECL(HttpRunControl, "HttpRunControl")
#endif

  }

}