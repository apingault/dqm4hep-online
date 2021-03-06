/// \file DQMModuleApplication.h
/*
 *
 * DQMModuleApplication.h header template automatically generated by a class generator
 * Creation date : dim. sept. 6 2015
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


#ifndef DQM4HEP_MODULEAPPLICATION_H
#define DQM4HEP_MODULEAPPLICATION_H

// -- dqm4hep headers
#include "dqm4hep/Internal.h"
#include "dqm4hep/StatusCodes.h"
#include "dqm4hep/RunControl.h"
#include "dqm4hep/XMLParser.h"
#include "dqm4hep/Application.h"
#include "dqm4hep/Cycle.h"
#include "dqm4hep/Module.h"
#include "dqm4hep/EventCollectorClient.h"
#include "dqm4hep/MonitorElementManager.h"

// -- tclap headers
#include "tclap/CmdLine.h"
#include "tclap/Arg.h"

namespace dqm4hep {

  namespace online {
    
    class ModuleApi;

    /** 
     *  @brief  ModuleApplication class
     */
    class ModuleApplication : public Application {
      friend class ModuleApi;
    public:
      /**
       *  @brief  Mode enumerator
       */
      enum Mode {
        UNDEFINED,
        ANALYSIS,
        STANDALONE
      };
      
      ModuleApplication(const ModuleApplication&) = delete;
      ModuleApplication& operator=(const ModuleApplication&) = delete;
      
      /** 
       *  @brief  Constructor
       */
      ModuleApplication();

      /** 
       *  @brief  Default destructor
       */
      ~ModuleApplication();

      /** 
       *  @brief  Get the module managed by this application
       */
      ModulePtr module() const;
      
      /**
       *  @brief  Get a pointer to the user module dynamic casted to a certain type
       */
      template <typename ModuleType>
      ModuleType *moduleAs();

      /** 
       *  @brief  Get the module name
       */
      const std::string &moduleName() const;

      /** 
       *  @brief  Get the module type
       */
      const std::string &moduleType() const;
      
      /**
       *  @brief  Get the application mode
       */
      Mode mode() const;
      
      /**
       *  @brief  Get the run control
       */
      const RunControl& runControl() const;
      
      /**
       *  @brief  Whether the application the application is in a state where booking monitor elements is allowed
       */
      bool allowBooking() const;
      
    private:
      void parseCmdLine(int argc, char **argv) override;
      void onInit() override;
      void onEvent(AppEvent *pAppEvent) override;
      void onStart() override;
      void onStop() override;
      
      /**
       *  @brief  Parse the input steering file
       *
       *  @param  fname the file name to parse
       */
      void parseSteeringFile(const std::string &fname);
      
      /**
       *  @brief  Configure the user module
       *
       *  @param element the xml element
       */
      void configureModule(core::TiXmlElement *element);
      
      /**
       *  @brief  Configure the application cycle
       *
       *  @param element the xml element
       */
      void configureCycle(core::TiXmlElement *element);
      
      /**
       *  @brief  Configure the network interface
       *
       *  @param element the xml element
       */
      void configureNetwork(core::TiXmlElement *element);
      
      /**
       *  @brief  Process the start of run service update
       *
       *  @param svc the service update content
       */      
      void processStartOfRun(ServiceUpdateEvent *svc);
      
      /**
       *  @brief  Process the end of run service update
       */
      void processEndOfRun();
      
      /**
       *  @brief  Receive an event from event collector and post it in the event loop
       *
       *  @param  event an event from the event collector
       */
      void receiveEvent(core::EventPtr event);
      
      /**
       *  @brief  Receive the new monitor element subscription list
       *  
       *  @param  cmd the network command buffer (json) 
       */
      void receiveSubscriptionList(CommandEvent *cmd);
      
      /**
       *  @brief  Slot to set the run number of all monitor elements on start of run
       *  
       *  @param  run the run description
       */
      void setElementsRunNumber(core::Run &run);
      
      /**
       *  @brief  Get the monitor element manager
       */
      std::shared_ptr<core::MonitorElementManager> monitorElementManager() const;
      
      /**
       *  @brief  Slot to post an event on standalone timer timeout
       */
      void postStandaloneProcess();
    
    private:  
      using CmdLine = std::shared_ptr<TCLAP::CmdLine>;
      using EventClientPtr = std::shared_ptr<EventCollectorClient>;
      using MonitorElementManagerPtr = std::shared_ptr<core::MonitorElementManager>;
      
      /**
       *  @brief  Priorities enumerator
       */
      enum Priorities {
        PROCESS_CALL = 50,
        END_OF_RUN = 60,
        END_OF_CYCLE = 70,
        SUBSCRIBE = 75,
        START_OF_RUN = 80
      };

    private:
      /// The user module type (plugin name)
      std::string                  m_moduleType = {""};
      /// The user module name (runtime defined)
      std::string                  m_moduleName = {""};
      /// The application run control
      RunControl                   m_runControl = {};
      /// The application running mode
      Mode                         m_mode = {UNDEFINED};
      /// The command line argument object
      CmdLine                      m_cmdLine = {nullptr};
      /// The XML parser to parse the input steering file
      core::XMLParser              m_parser = {};
      /// The user module plugin 
      ModulePtr                    m_module = {nullptr};
      /// The cycle object managing cycles in the application
      Cycle                        m_cycle;
      /// The event collector client to receive events from collector
      EventClientPtr               m_eventCollectorClient = {nullptr};
      /// The event source from the event collector
      std::string                  m_eventSourceName = {""};
      /// The current number of events in the event loop
      std::atomic_uint             m_currentNQueuedEvents = {0};
      /// The maximum of queued events to be processed (sub-sampling)
      unsigned int                 m_eventQueueSize = {100};
      /// The timer for the standalone module mode
      AppTimer*                    m_standaloneTimer = {nullptr};
      /// The time between two consecutive standalone module process (unit ms)
      unsigned int                 m_standaloneSleep = {1000};
      /// The monitor element manager
      MonitorElementManagerPtr     m_monitorElementManager = {nullptr};
      /// Whether the application for monitor element booking (state variable)
      bool                         m_allowBooking = {false};
    };
    
    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------
    
    template <typename ModuleType>
    inline ModuleType *ModuleApplication::moduleAs() {
      return dynamic_cast<ModuleType*>(m_module.get());
    }

  }

} 

#endif  //  DQM4HEP_MODULEAPPLICATION_H
