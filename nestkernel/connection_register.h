/*
 *  connection_register.h
 *
 *  This file is part of NEST.
 *
 *  Copyright (C) 2004 The NEST Initiative
 *
 *  NEST is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  NEST is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with NEST.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef CONNECTION_REGISTER_H
#define CONNECTION_REGISTER_H

#include "nest_time.h"
#include "dictdatum.h"

namespace nest
{
  class TimeConverter;
  
  class ConnectionRegister
  {
  public:
    
    
    size_t get_num_connections() const;
    
    void incr_connections();
    
    const Time& get_min_delay() const;

    const Time& get_max_delay() const;

    void update_delay_extrema( const double_t mindelay_cand, const double_t maxdelay_cand );
    
    /**
     * Raise exception if delay value in milliseconds is invalid.
     *
     * @note Not const, since it may update delay extrema as a side-effect.
     */
    void assert_valid_delay_ms( double_t );
    
    /**
     * Raise exception if either of the two delays in steps is invalid.
     *
     * @note Setting continuous delays requires testing d and d+1. This function
     *       implements this more efficiently than two calls to assert_valid_delay().
     * @note This test accepts the delays in steps, as this makes more sense when
     *       working with continuous delays.
     * @note Not const, since it may update delay extrema as a side-effect.
     */
    void assert_two_valid_delays_steps( long_t, long_t );

    bool get_user_set_delay_extrema() const;
    
    void calibrate( const TimeConverter& );
    
    void used_default_delay();
    
    void get_status( DictionaryDatum& ) const;
    void set_status( const DictionaryDatum& );
    
  private:
    Time min_delay_;                 //!< Minimal delay of all created synapses.
    Time max_delay_;                 //!< Maximal delay of all created synapses.
    size_t num_connections_;         //!< The number of connections registered with this type
    bool default_delay_needs_check_; //!< Flag indicating, that the default delay must be checked
    bool user_set_delay_extrema_;    //!< Flag indicating if the user set the delay extrema.
    bool used_default_delay_;
  };
  
  inline const Time&
  ConnectionRegister::get_min_delay() const
  {
    return min_delay_;
  }
  
  inline const Time&
  ConnectionRegister::get_max_delay() const
  {
    return max_delay_;
  }
  
  inline bool
  ConnectionRegister::get_user_set_delay_extrema() const
  {
    return user_set_delay_extrema_;
  }
  
  inline size_t
  ConnectionRegister::get_num_connections() const
  {
    return num_connections_;
  }
  
  inline void
  ConnectionRegister::incr_connections()
  {
    ++num_connections_;
  }
}





#endif /* CONNECTION_REGISTER_H */
