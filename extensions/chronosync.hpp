/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2015  Regents of the University of California.
 *
 * This file is part of ndnSIM. See AUTHORS for complete list of ndnSIM authors and
 * contributors.
 *
 * ndnSIM is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * ndnSIM is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * ndnSIM, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Spyridon (Spyros) Mastorakis <mastorakis@cs.ucla.edu>
 */

#include "socket.hpp"

#include <ndn-cxx/face.hpp>

namespace ndn {

class ChronoSync
{
public:
  ChronoSync(const int minNumberMessages, const int maxNumberMessages);

  void
  setSyncPrefix(const Name& syncPrefix);

  void
  setUserPrefix(const Name& userPrefix);

  void
  setRoutingPrefix(const Name& routingPrefix);

  void
  delayedInterest(int id);

  void
  publishDataPeriodically(int id);

  void
  printData(const shared_ptr<const Data>& data);

  void
  processSyncUpdate(const std::vector<chronosync::MissingDataInfo>& updates);

  void
  initializeSync();

  void
  run();

  void
  runPeriodically();

private:
  boost::asio::io_service m_ioService;
  Face m_face;
  Scheduler m_scheduler;

  Name m_syncPrefix;
  Name m_userPrefix;
  Name m_routingPrefix;
  Name m_routableUserPrefix;

  shared_ptr<chronosync::Socket> m_socket;

  boost::mt19937 m_randomGenerator;
  boost::variate_generator<boost::mt19937&, boost::uniform_int<> > m_rangeUniformRandom;
  boost::variate_generator<boost::mt19937&, boost::uniform_int<> > m_messagesUniformRandom;

  int m_numberMessages;
};

} // namespace ndn
