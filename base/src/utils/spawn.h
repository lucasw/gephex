#ifndef INCLUDED_SPAWN_H
#define INCLUDED_SPAWN_H

#include <vector>
#include <string>

namespace utils
{
	/**
	 * Executes an executable in a new process.
	 * The calling process is not suspended but returns immediately.
         *
         * Note that it is possible that execution of the file fails
         * without an exception thrown.
         *
         * If exec_name is not an absolute path it is searched in the
         * current path (as set by the os's environment variables).
         *
         * \param exec_name the filename of the executable that is executed
         * \param args a vector of arguments that are passed to the
         *             binary. Don't pass the exec_name as first parameter -
         *             this is already done internally. If an argument
         *             contains whitespace it's your responsibility to
         *             quote them.
	 *
	 * \throws std::runtime_error if forking or execution of the 
         *                            binary fails	
	 */
	void spawn(const std::string& exec_name,
                   const std::vector<std::string>& args);
}

#endif
