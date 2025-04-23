// Copyright 2009, Willow Garage, Inc. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of the  Willow Garage, Inc. nor the names of its
//      contributors may be used to endorse or promote products derived from
//      this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef RESOURCE_RETRIEVER__RETRIEVER_HPP_
#define RESOURCE_RETRIEVER__RETRIEVER_HPP_

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "resource_retriever/exception.hpp"
#include "resource_retriever/memory_resource.hpp"
#include "resource_retriever/plugins/retriever_plugin.hpp"
#include "resource_retriever/resource.hpp"
#include "resource_retriever/visibility_control.hpp"

namespace resource_retriever
{

using RetrieverPluginSharedPtr = std::shared_ptr<plugins::RetrieverPlugin>;
using RetrieverVec = std::vector<RetrieverPluginSharedPtr>;

RetrieverVec RESOURCE_RETRIEVER_PUBLIC default_plugins();

/**
 * \brief Retrieves files from from a url. Caches a CURL handle so multiple accesses to a single url
 * will keep connections open.
 */
class Retriever
{
public:
  RESOURCE_RETRIEVER_PUBLIC
  explicit Retriever(RetrieverVec plugins = default_plugins());

  RESOURCE_RETRIEVER_PUBLIC
  ~Retriever();

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4996)
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
  /**
   * \brief Get a file and store it in memory
   * \param url The url to retrieve. package://package/file will be turned into the correct file:// invocation
   * \return The file, loaded into memory
   * \throws resource_retriever::Exception if anything goes wrong.
   */
  [[deprecated("Use get_shared(const std::string & url) instead.")]]
  RESOURCE_RETRIEVER_PUBLIC
  MemoryResource get(const std::string & url);
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif

/**
   * \brief Get a file and store it in memory
   * \param url The url to retrieve. package://package/file will be turned into the correct file:// invocation
   * \return The file, loaded into memory
   * \throws resource_retriever::Exception if anything goes wrong.
   */
  RESOURCE_RETRIEVER_PUBLIC
  ResourceSharedPtr get_shared(const std::string & url);

private:
  RetrieverVec plugins;
};

}  //  namespace resource_retriever

#endif  //  RESOURCE_RETRIEVER__RETRIEVER_HPP_
