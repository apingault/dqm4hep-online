  /// \file DQMModuleApplication.cc
/*
 *
 * DQMModuleApplication.cc source template automatically generated by a class generator
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

// -- dqm4hep headers
#include "dqm4hep/DQMModuleApplication.h"
#include "dqm4hep/DQMMonitorElementSender.h"
#include "dqm4hep/DQMMonitorElementManager.h"

namespace dqm4hep
{

DQMModuleApplication::DQMModuleApplication() :
		m_isInitialized(false),
		m_shouldStop(false),
		m_pModule(NULL),
		m_pMonitorElementManager(NULL),
		m_pMonitorElementSender(NULL)
{
	m_pMonitorElementManager = new DQMMonitorElementManager();
	m_pMonitorElementSender = new DQMMonitorElementSender(this);
}

//-------------------------------------------------------------------------------------------------

DQMModuleApplication::~DQMModuleApplication() 
{
	delete m_pMonitorElementManager;
	delete m_pMonitorElementSender;

	if(m_pModule)
		delete m_pModule;
}

//-------------------------------------------------------------------------------------------------

StatusCode DQMModuleApplication::exit( int returnCode )
{
	LOG4CXX_INFO( dqmMainLogger , "Exiting module application ..." );

	if(!this->isInitialized())
		return STATUS_CODE_NOT_INITIALIZED;

	if( returnCode >= 0 && returnCode < NUMBER_OF_STATUS_CODES )
		m_returnCode = static_cast< StatusCode >( returnCode );
	else
		m_returnCode = STATUS_CODE_FAILURE;

	this->setStopApplication(true);

	LOG4CXX_INFO( dqmMainLogger , "Exiting module application ... OK" );

	return m_returnCode;
}

//-------------------------------------------------------------------------------------------------

DQMModule *DQMModuleApplication::getModule() const
{
	return m_pModule;
}

//-------------------------------------------------------------------------------------------------

bool DQMModuleApplication::shouldStopApplication() const
{
	return m_shouldStop;
}

//-------------------------------------------------------------------------------------------------

void DQMModuleApplication::setStopApplication(bool stopApplication)
{
	m_shouldStop = stopApplication;
}

//-------------------------------------------------------------------------------------------------

StatusCode DQMModuleApplication::setModuleName(const std::string &name)
{
	if(this->isInitialized())
		return STATUS_CODE_ALREADY_INITIALIZED;

	m_moduleName = name;

	if(m_pModule)
		m_pModule->setName(name);

	return STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

StatusCode DQMModuleApplication::setModuleType(const std::string &type)
{
	if(this->isInitialized())
		return STATUS_CODE_ALREADY_INITIALIZED;

	m_moduleType = type;

	return STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

const std::string &DQMModuleApplication::getModuleName() const
{
	if(m_pModule)
		return m_pModule->getName();

	return m_moduleName;
}

//-------------------------------------------------------------------------------------------------

const std::string &DQMModuleApplication::getModuleType() const
{
	return m_moduleType;
}

//-------------------------------------------------------------------------------------------------

bool DQMModuleApplication::isInitialized() const
{
	return m_isInitialized;
}

//-------------------------------------------------------------------------------------------------

StatusCode DQMModuleApplication::getReturnCode() const
{
	return m_returnCode;
}

//-------------------------------------------------------------------------------------------------

void DQMModuleApplication::setInitialized(bool initialized)
{
	m_isInitialized = initialized;
}

//-------------------------------------------------------------------------------------------------

DQMMonitorElementManager *DQMModuleApplication::getMonitorElementManager() const
{
	return m_pMonitorElementManager;
}

//-------------------------------------------------------------------------------------------------

DQMMonitorElementSender *DQMModuleApplication::getMonitorElementSender() const
{
	return m_pMonitorElementSender;
}

//-------------------------------------------------------------------------------------------------

StatusCode DQMModuleApplication::setModule(DQMModule *pModule)
{
	if(!pModule)
		return STATUS_CODE_INVALID_PTR;

	m_pModule = pModule;
	m_pModule->setName(m_moduleName);
	m_pModule->setModuleApplication(this);

	return STATUS_CODE_SUCCESS;
}

} 

