# homeLab — Hospital IT Architecture Simulation

**homeLab** is a comprehensive portfolio project designed to simulate a **hospital IT environment**, demonstrating how modern healthcare systems are structured, integrated, and maintained. The project serves as both a **learning resource** for students and professionals and a **technical reference** for hospital IT infrastructure design.

##  Project Overview

Hospitals rely on complex IT ecosystems to manage patient data, medical imaging, and clinical workflows. This project simulates key components of a hospital IT environment, including:  

- **Hospital Information Systems (HIS)**  
- **Radiology Information Systems (RIS)**  
- **Picture Archiving and Communication Systems (PACS)**  
- **IoT devices and sensor networks**  
- **Virtualized and containerized infrastructure**  

The repository illustrates how these components interact, emphasizing **integration, monitoring, and system maintenance**.


##  Key Features

1. **Virtualization & Containerization**  
   - Use of **Proxmox VE**, **LXC containers**, and **VMs** to simulate hospital servers and services.  
   - Modular design allowing easy extension or modification.

2. **Integration & Communication Standards**  
   - Implementation of healthcare protocols like **HL7**, **HL7 CDA**, and **DICOM**.  
   - Examples of integrating PACS, HIS, and RIS systems.

3. **Monitoring & Backoffice Tools**  
   - Scripts and applications in **Python** and **C#** for system monitoring.  
   - Tools for logging, error detection, and workflow tracking.

4. **IoT Subsystems**  
   - Integration of sensors using **MQTT** for device monitoring.  
   - Back-office application for sensor activity tracking and data analysis.

5. **Network & Security**  
   - VPN tunnels, router configurations (**MikroTik**), and network segmentation.  
   - Understanding of **ISO/OSI networking layers** and virtual network administration.

6. **Cloud & Storage**  
   - Use of **Amazon S3** for scalable storage solutions.  
   - Hybrid deployment combining on-premises and cloud-based infrastructure.


## Project Structure

```text
homeLab/
│
├─ README.md              # Project overview
├─ Schematy.md            # Architecture diagrams and design
├─ VM.md                  # Virtual Machine configurations
├─ VPS.md                 # VPS configurations
├─ FHIR.md                # Health IT protocols (FHIR, HL7)
├─ mqtt.md                # IoT messaging using MQTT
├─ LXC.md                 # LXC container setups
├─ nginxansible.md        # NGINX configuration using Ansible
├─ AD.md                  # Active Directory setup
└─ zdj/                   # Images and diagrams illustrating the architecture
```

## Technologies Used
- Programming & Scripting: Python, C# (WinForms), Bash
- Web & Frontend: React, React Native, Java, Git
- Medical IT Systems: PACS, HIS, RIS
- Protocols & Integration: HL7, HL7 CDA, DICOM
- Virtualization & Containers: Proxmox VE, LXC, VMware
- Cloud & Storage: Amazon S3
- Networking & Security: VPN, Mikrotik routers, ISO/OSI layers

## Learning Outcomes
Through this project, users can:
- Understand the architecture and workflow of hospital IT systems.
- Gain experience with system integration using healthcare standards.
- Learn to develop monitoring and back-office applications for medical devices and servers.
- Explore virtualization, containerization, and cloud deployments in a healthcare context.
- Practice network configuration, security, and infrastructure management.