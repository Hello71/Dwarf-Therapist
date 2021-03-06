/*
Dwarf Therapist
Copyright (c) 2009 Trey Stout (chmod)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef DFINSTANCE_LINUX_H
#define DFINSTANCE_LINUX_H
#include "dfinstancenix.h"

class DFInstanceLinux : public DFInstanceNix {
    Q_OBJECT
public:
    DFInstanceLinux(QObject *parent=0);
    virtual ~DFInstanceLinux();
    void find_running_copy();

    size_t read_raw_ptrace(const VPTR addr, const size_t bytes, void *buffer);
    size_t read_raw(const VPTR addr, const size_t bytes, void *buffer);

    // Writing
    size_t write_raw_ptrace(const VPTR addr, const size_t bytes, const void *buffer);
    size_t write_raw(const VPTR addr, const size_t bytes, const void *buffer);

    bool attach();
    bool detach();

protected:
    bool set_pid();
    virtual bool mmap(size_t size);
    virtual bool mremap(size_t new_size);

private:
    int wait_for_stopped();
    ssize_t process_vm(long number, const VPTR addr, const size_t bytes, void *buffer);
    long remote_syscall(int syscall_id,
                          long arg0 = 0, long arg1 = 0, long arg2 = 0,
                          long arg3 = 0, long arg4 = 0, long arg5 = 0);

    QFile m_memory_file;
    bool m_warned_pvm;
};

#endif // DFINSTANCE_H
