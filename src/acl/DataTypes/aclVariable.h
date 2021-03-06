/*
 * Advanced Simulation Library <http://asl.org.il>
 * 
 * Copyright 2015 Avtech Scientific <http://avtechscientific.com>
 *
 *
 * This file is part of Advanced Simulation Library (ASL).
 *
 * ASL is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, version 3 of the License.
 *
 * ASL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with ASL. If not, see <http://www.gnu.org/licenses/>.
 *
 */


#ifndef ACLVARIABLE_H
#define ACLVARIABLE_H

#include "../aclElementBase.h"
#include "../../aslUtilities.h"
#include "../aclUtilities.h"

using namespace asl;

namespace acl
{

	template <typename T> class Variable: public ElementBase
	{
		private:
			T value;
			string name;
			static const string prefix;
			static unsigned int id;
		public:
			explicit Variable(T v);
			virtual string str(const KernelConfiguration & kernelConfig) const;
			virtual string getName() const;
			virtual string getTypeSignature(const KernelConfiguration & kernelConfig) const;
			virtual string getLocalDeclaration(const KernelConfiguration & kernelConfig) const;
			virtual void addToKernelSource(vector<Element> & arguments,
			                               vector<Element> & localDeclarations) const;
			virtual void setAsArgument(cl::Kernel & kernel, unsigned int argumentIndex) const;
			virtual const T getValue() const;
			void setValue(const T & a);
	};


	template <typename T> Variable<T>::Variable(T v):
		ElementBase(true, 0, typeToTypeID<T>()),
		value(v)
	{
		++id;
		name = prefix + asl::numToStr(id);
	}


	template <typename T> string Variable<T>::getName() const
	{
		return name;
	}


	template <typename T> string Variable<T>::str(const KernelConfiguration & kernelConfig) const
	{
		return name;
	}

	template <typename T> string Variable<T>::getLocalDeclaration(const KernelConfiguration & kernelConfig) const
	{
		return "";
	}


	template <typename T> void Variable<T>::addToKernelSource(vector<Element> & arguments,
	                                                          vector<Element> & localDeclarations) const
	{
	}


	template <typename T> void Variable<T>::setAsArgument(cl::Kernel & kernel, unsigned int argumentIndex) const
	{
		cl_int status = 0;		
		status = kernel.setArg(argumentIndex, value);
		errorMessage(status, "Kernel::setArg() - " + name + ", argument " + asl::numToStr(argumentIndex));
	}


	template <typename T>  const T Variable<T>::getValue() const
	{
		return value;
	}


	template <typename T> void Variable<T>::setValue(const T & a)
	{
		value = a;
	}

		
} // namespace acl

#endif // ACLVARIABLE_H
