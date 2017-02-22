/// \file RunControlInterface.h
/*
*
* RunControlInterface.h header template automatically generated by a class generator
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


#ifndef RUNCONTROLINTERFACE_H
#define RUNCONTROLINTERFACE_H

#include "dqm4hep/Run.h"
#include "dqm4hep/RunControl.h"

namespace dqm4hep {

  namespace core {

    class ConfigurationHandle;

    /**
     * RunControlInterface class
     *
     * Main user interface to connect to an external run control instance.
     * This interface must be implemented by user and declared as a plugin.
     * This plugin will be loaded in a run control server as used as the main
     * interface to receive start and stop signal from an external run control.
     *
     * WARNING : The current implementation of the run control process supposes
     * that the signal handling in this class is done in a separate thread.
     *
     * On server startup/shutdown, the user will be notifier=d using the callback
     * functions onServerStartup() and onServerShutdown().
     *
     * To start a new run or end the current one, user can call the startNewRun()
     * and endCurrentRun() functions. By doing so, all listening clients of the
     * run control server will be notified.
     */
    class RunControlInterface
    {
      friend class RunControlServer;
    public:
      /**
       * Constructor
       */
      RunControlInterface();

      /**
       * Destructor
       */
      virtual ~RunControlInterface();

      /**
       * Callback method on run control server startup
       */
      virtual void onServerStartup() {}

      /**
       * Callback method on run control server shutdown
       */
      virtual void onServerShutdown() {}

      /**
       * Read user settings from configuration handle
       *
       * @param handle the configuration handle
       */
       virtual StatusCode readSettings(const ConfigurationHandle &handle) = 0;

    protected:
      /**
       * Start a new run.
       *
       * @param run the run to start
       * @param password an optional password required to start the new run
       */
      void startNewRun(const Run &run, const std::string &password = "");

      /**
       * End the current run
       *
       * @param password an optional password required to stop the current run
       */
      void endCurrentRun(const std::string &password = "");

    private:
      /**
       * Set the run control for his interface
       *
       * @param pRunControl the run control instance
       */
      void setRunControl(RunControl *pRunControl);

    private:
      RunControl                    *m_pRunControl;   ///< The run control instance
    };

  }

}

#endif  //  RUNCONTROLINTERFACE_H
