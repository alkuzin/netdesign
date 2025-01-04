/**
 * NetDesign - simple network design tool.
 * Copyright (C) 2025 Alexander (@alkuzin)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef NET_DESIGN_PROJECT_CONTEXT_HPP
#define NET_DESIGN_PROJECT_CONTEXT_HPP

#include <boost/numeric/ublas/matrix.hpp>
#include <NetDesign/Channel.hpp>
#include <NetDesign/Router.hpp>
#include <NetDesign/Node.hpp>
#include <vector>


namespace netd {

namespace ublas = boost::numeric::ublas;

struct ProjectContext {
    ublas::matrix<uint32_t> loadMatrix;
    std::vector<Channel>    channels;
    std::vector<Router>     routers;
    std::vector<Node>       nodes;
    uint32_t                packetSize;
};

extern ProjectContext projectContext;

} // namespace netd

#endif // NET_DESIGN_PROJECT_CONTEXT_HPP