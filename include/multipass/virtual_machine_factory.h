/*
 * Copyright (C) 2017-2019 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef MULTIPASS_VIRTUAL_MACHINE_FACTORY_H
#define MULTIPASS_VIRTUAL_MACHINE_FACTORY_H

#include <multipass/fetch_type.h>
#include <multipass/virtual_machine.h>
#include <multipass/vm_image.h>

namespace YAML
{
class Node;
}

namespace multipass
{
class VirtualMachineDescription;
class VMImageHost;
class VMStatusMonitor;
class VirtualMachineFactory
{
public:
    using UPtr = std::unique_ptr<VirtualMachineFactory>;
    virtual ~VirtualMachineFactory() = default;
    virtual VirtualMachine::UPtr create_virtual_machine(const VirtualMachineDescription& desc,
                                                        VMStatusMonitor& monitor) = 0;

    /** Removes any resources associated with a VM of the given name.
     *
     * @param name The unique name assigned to the virtual machine
     */
    virtual void remove_resources_for(const std::string& name) = 0;

    virtual FetchType fetch_type() = 0;
    virtual VMImage prepare_source_image(const VMImage& source_image) = 0;
    virtual void prepare_instance_image(const VMImage& instance_image, const VirtualMachineDescription& desc) = 0;
    virtual void configure(const std::string& name, YAML::Node& meta_config, YAML::Node& user_config) = 0;
    virtual void check_hypervisor_support() = 0;
    virtual QString get_backend_directory_name() = 0;

protected:
    VirtualMachineFactory() = default;
    VirtualMachineFactory(const VirtualMachineFactory&) = delete;
    VirtualMachineFactory& operator=(const VirtualMachineFactory&) = delete;
};
}
#endif // MULTIPASS_VIRTUAL_MACHINE_FACTORY_H
