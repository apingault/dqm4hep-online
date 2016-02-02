  /// \file DQMMessaging.cc
/*
 *
 * DQMMessaging.cc source template automatically generated by a class generator
 * Creation date : lun. ao�t 17 2015
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
#include "dqm4hep/DQMMessaging.h"
#include "dqm4hep/DQMMonitorElement.h"
#include "dqm4hep/DQMDataStream.h"

namespace dqm4hep
{

StatusCode DQMMonitorElementPublication::serialize(DQMDataStream *const pDataStream) const
{
	dqm_uint mapSize = this->size();
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->write(mapSize));

	for(std::map<std::string, std::vector<DQMMonitorElement *> >::const_iterator iter = this->begin(), endIter = this->end() ;
		endIter != iter ; ++iter)
	{
		std::string moduleName(iter->first);
		DQMMonitorElementList meList(iter->second);

		RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->write(moduleName));
		RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->write((dqm_uint)meList.size()));

		for(unsigned int i=0 ; i<meList.size() ; i++)
		{
			DQMMonitorElement *pMonitorElement = meList.at(i);
			RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, pMonitorElement->serialize(pDataStream));
		}
	}

	return STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

StatusCode DQMMonitorElementPublication::deserialize(DQMDataStream *const pDataStream)
{
	dqm_uint mapSize = 0;
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->read(mapSize));

	for(unsigned int i=0 ; i<mapSize ; i++)
	{
		std::string moduleName;
		RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->read(moduleName));

		dqm_uint meListSize = 0;
		RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->read(meListSize));

		DQMMonitorElementList meList;

		for(unsigned int i=0 ; i<meListSize ; i++)
		{
			DQMMonitorElement *pMonitorElement = new DQMMonitorElement();

			PROCESS_CODE_IF_AND_RETURN(STATUS_CODE_SUCCESS, !=, pMonitorElement->deserialize(pDataStream),
					delete pMonitorElement;
			);

			meList.push_back(pMonitorElement);
		}

		(*this)[moduleName] = meList;
	}

	return STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

StatusCode DQMMonitorElementInfo::serialize(DQMDataStream *const pDataStream) const
{
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->write(m_moduleName));
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->write(m_monitorElementFullPath));
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->write(m_monitorElementName));
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->write(m_monitorElementDescription));
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->write(m_monitorElementType));

	return STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

StatusCode DQMMonitorElementInfo::deserialize(DQMDataStream *const pDataStream)
{
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->read(m_moduleName));
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->read(m_monitorElementFullPath));
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->read(m_monitorElementName));
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->read(m_monitorElementDescription));
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->read(m_monitorElementType));

	return STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

StatusCode DQMMonitorElementInfoList::serialize(DQMDataStream *const pDataStream) const
{
	dqm_uint nMonitorElementInfo = size();
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->write(nMonitorElementInfo));

	for(unsigned int i=0 ; i<nMonitorElementInfo ; i++)
	{
		RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, this->at(i).serialize(pDataStream));
	}

	return STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

StatusCode DQMMonitorElementInfoList::deserialize(DQMDataStream *const pDataStream)
{
	clear();

	dqm_uint nMonitorElement = 0;
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->read(nMonitorElement));

	for(unsigned int i=0 ; i<nMonitorElement ; i++)
	{
		DQMMonitorElementInfo info;
		RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, info.deserialize(pDataStream));

		this->push_back(info);
	}

	return STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

StatusCode DQMCollectorInfo::serialize(DQMDataStream *const pDataStream) const
{
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->write(m_systemName));
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->write(m_nodeName));
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->write(m_release));
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->write(m_version));
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->write(m_machine));
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->write(m_hostName));

	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->write((dqm_uint)m_moduleListName.size()));

	for(unsigned int i=0 ; i<m_moduleListName.size() ; i++)
		RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->write(m_moduleListName.at(i)));

	return STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

StatusCode DQMCollectorInfo::deserialize(DQMDataStream *const pDataStream)
{
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->read(m_systemName));
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->read(m_nodeName));
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->read(m_release));
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->read(m_version));
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->read(m_machine));
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->read(m_hostName));

	dqm_uint nModules = 0;
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->read(nModules));

	for(unsigned int i=0 ; i<nModules ; i++)
	{
		std::string moduleName;
		RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->read(moduleName));
		m_moduleListName.push_back(moduleName);
	}

	return STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

StatusCode DQMMonitorElementListNameRequest::serialize(DQMDataStream *const pDataStream) const
{
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->write(m_moduleName));
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->write(m_monitorElementName));
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->write(m_detectorName));
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->write((dqm_uint)m_monitorElementType));

	return STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

StatusCode DQMMonitorElementListNameRequest::deserialize(DQMDataStream *const pDataStream)
{
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->read(m_moduleName));
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->read(m_monitorElementName));
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->read(m_detectorName));
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->read((dqm_uint &)m_monitorElementType));

	return STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

StatusCode DQMMonitorElementRequest::serialize(DQMDataStream *const pDataStream) const
{
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->write((dqm_uint)this->size()));

	for(unsigned int i=0 ; i<this->size() ; i++)
	{
		RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->write(this->at(i).first));
		RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->write(this->at(i).second));
	}

	return STATUS_CODE_SUCCESS;
}

//-------------------------------------------------------------------------------------------------

StatusCode DQMMonitorElementRequest::deserialize(DQMDataStream *const pDataStream)
{
	dqm_uint requestListSize = 0;
	RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->read(requestListSize));

	for(unsigned int i=0 ; i<requestListSize ; i++)
	{
		value_type requestedPair;

		RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->read(requestedPair.first));
		RETURN_RESULT_IF(dqm4hep::STATUS_CODE_SUCCESS, !=, pDataStream->read(requestedPair.second));

		this->push_back(requestedPair);
	}

	return STATUS_CODE_SUCCESS;
}


} 

