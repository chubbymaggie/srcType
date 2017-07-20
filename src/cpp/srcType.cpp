/**
 * @file srcType.cpp
 *
 * @copyright Copyright (C) 2013-2014  SDML (www.srcML.org)
 *
 * The srcML Toolkit is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * The srcML Toolkit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the srcML Toolkit; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include <srcType.hpp>
#include <srcTypeHandler.hpp>
#include <srcTypeInferencePolicy.hpp>
namespace srcTypeNS{
    srcType::srcType(){} 
    srcType::srcType(const char* filename, const bool inferTypes = false){
        srcTypePolicy* policy = new srcTypePolicy();
        srcSAXController control(filename);
        srcSAXEventDispatch::srcSAXEventDispatcher<> handler {policy};
        control.parse(&handler); //Start parsing
        data = policy->GetDictionary();
    }
    srcType::srcType(std::string buffer, const bool inferTypes = false){
        srcTypePolicy* srcTypepol = new srcTypePolicy();
        srcSAXController control(buffer);
        srcSAXEventDispatch::srcSAXEventDispatcher<> srcTypehandler {srcTypepol};
        control.parse(&srcTypehandler); //Start parsing
        data = srcTypepol->GetDictionary();
        //delete srcTypepol; 
        if(inferTypes){
            srcSAXController infcontrol(buffer);
            srcTypeInferencePolicy* srcTypeInferencePol = new srcTypeInferencePolicy(this);
            srcSAXEventDispatch::srcSAXEventDispatcher<> inferenceHandler({srcTypeInferencePol}, true);
            infcontrol.parse(&inferenceHandler);
        }
    }
    srcType::srcType(FILE* file, const bool inferTypes = false){
        //srcSAXController control(file);
        //srcTypeHandler handler(&dictionary);
        //control.parse(&handler);
    }
    srcType::srcType(int fd, const bool inferTypes = false){
        //srcSAXController control(fd);
        //srcTypeHandler handler(&dictionary);
        //control.parse(&handler);
    }
    void srcType::ReadArchiveFile(std::string filename){
        srcTypePolicy* policy = new srcTypePolicy();
        srcSAXController control(filename.c_str());
        srcSAXEventDispatch::srcSAXEventDispatcher<> handler {policy};
        control.parse(&handler); //Start parsing
        data = policy->GetDictionary();
    }
}