
Name: Abhinav Bathe <br>
Roll Number: 53 <br>
Batch: C2 <br>
PRN: 1032222447 <br>
Course: DCC

---


# Bully Election Algorithm

## Overview

This project implements the Bully Election Algorithm used in distributed systems to select a coordinator (leader) among processes.

Each process has a unique ID, and the process with the highest ID among active processes becomes the coordinator.

---

## Features

* Input number of processes and their status (active or failed)
* Automatically determines the initial coordinator
* Supports simulation of:

  * Process failure
  * Process recovery
  * Election process
* Displays the current coordinator
* Menu-driven interface for user interaction

---

## Algorithm Concept

The Bully Algorithm works as follows:

1. When a process detects that the coordinator has failed, it initiates an election.
2. It sends election messages to all processes with higher IDs.
3. If no higher process responds, it becomes the coordinator.
4. If a higher process responds, that process continues the election.
5. Eventually, the highest active process becomes the new coordinator.

---

## Menu Options

1. Display Processes
2. Fail a Process
3. Recover a Process
4. Start Election
5. Show Coordinator
6. Exit

---

## Example

```
Enter number of processes: 5
Process 1: 1
Process 2: 1
Process 3: 0
Process 4: 1
Process 5: 1

Current Coordinator is Process 5
```

---


# Basic Chatbot Deployment - DCC LCA:2

**Application URL:** https://dcclca2-eight.vercel.app  
**Password:** 123456

## Overview

This project is a simple chatbot application that uses the Google Gemini API to generate responses. It is deployed on a cloud platform and includes basic password protection.

---

## Features

* Chat interface for user interaction
* Integration with the Gemini API
* Password-based access control
* Deployment using Vercel
* Clean and responsive user interface

---

## Architecture

```
Frontend
   ↓
Backend
   ↓
Gemini API
```

---

## Deployment

### Platform

* Vercel

### Steps

1. Push the project code to GitHub
2. Import the repository into Vercel
3. Configure environment variables:

   * GEMINI_API_KEY
   * APP_PASSWORD
4. Deploy the application

---

## Output

* Chat interface with real-time responses
* Password-protected access
* Hosted cloud application

---

# Network File System (NFS)

## Definition:

Network File System (NFS) is a distributed file system protocol that allows a user on a client computer to access files over a network as if they were stored locally on their own system.

---

## Procedure

### Step 1: System Preparation

Update the system and install required NFS packages.

**Commands:**

```
sudo apt update
sudo apt install nfs-kernel-server nfs-common -y
```

---

### Step 2: Server Configuration

Create a directory to be shared and assign appropriate permissions.

**Commands:**

```
sudo mkdir -p /nfs/shared
sudo chmod 777 /nfs/shared
```

Create a sample file:

```
echo "Hello NFS" | sudo tee /nfs/shared/test.txt
```

---

### Step 3: Export Configuration

Open configuration file:

```
sudo nano /etc/exports
```

Write entry:

```
/nfs/shared *(rw,sync,no_subtree_check,no_root_squash)
```

Apply configuration:

```
sudo exportfs -a
```

---

### Step 4: Service Management

Start/restart NFS service:

```
sudo systemctl restart nfs-kernel-server
```

or

```
sudo service nfs-kernel-server start
```

---

### Step 5: Client Configuration

Create mount point:

```
sudo mkdir -p /mnt/nfs
```

Mount shared directory:

```
sudo mount localhost:/nfs/shared /mnt/nfs
```

---

### Step 6: Verification

List contents:

```
ls /mnt/nfs
```

Create file:

```
echo "Client File" | sudo tee /mnt/nfs/client.txt
```

Verify on server:

```
ls /nfs/shared
```

---

