/*
 * Copyright (c) 2014-2015 Enrico M. Crisostomo
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 3, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef FSW_FSEVENT_MONITOR_H
#  define FSW_FSEVENT_MONITOR_H

#  include "monitor.hpp"
#  include <CoreServices/CoreServices.h>
#  ifdef HAVE_CXX_MUTEX
#    include <mutex>
#  endif
namespace fsw
{
  class fsevents_monitor : public monitor
  {
    REGISTER_MONITOR(fsevents_monitor, fsevents_monitor_type);

  public:
    fsevents_monitor(std::vector<std::string> paths,
                     FSW_EVENT_CALLBACK *callback,
                     void *context = nullptr);
    virtual ~fsevents_monitor();

  protected:
    void run() override;
    void on_stop() override;

  private:
    fsevents_monitor(const fsevents_monitor& orig) = delete;
    fsevents_monitor& operator=(const fsevents_monitor& that) = delete;

    static void fsevents_callback(ConstFSEventStreamRef streamRef,
                                  void *clientCallBackInfo,
                                  size_t numEvents,
                                  void *eventPaths,
                                  const FSEventStreamEventFlags eventFlags[],
                                  const FSEventStreamEventId eventIds[]);

#  ifdef HAVE_CXX_MUTEX
    std::mutex run_mutex;
#  endif
    FSEventStreamRef stream = nullptr;
    CFRunLoopRef run_loop = nullptr;
  };
}

#endif  /* FSW_FSEVENT_MONITOR_H */
