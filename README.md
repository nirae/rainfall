# Rainfall
## Second projet sécurité de l'École 42

Rainfall est un iso de challenge légèrement plus complexe que Snow Crash qui vous plongera dans les méandres du reverse engineering et vous apprendra à reconstruire un code et à en comprendre son fonctionnement afin d'en dénicher les failles. Pourrez-vous atteindre le dernier level ?

### Setup de la VM

Réseau Virtualbox NAT -> Redirection de port

- **Nom :** SSH
- **Protocole :** TCP
- **Ip hôte :** 127.0.0.1
- **Port hote :** 4242
- **Ip invitée :** 10.0.2.15 (ip donnée par virtualbox, peut être différente)
- **Port invitée :** 4242 (port ssh de l'iso)

#### SSH / SCP

	ssh -p 4242 levelXX@127.0.0.1
	scp -P 4242 levelXX@127.0.0.1:/path/on/the/vm ./path/on/my/machine

:warning: :warning: :warning: :warning: :warning: :warning: :warning: :warning: :warning: :warning:

### !!! SPOIL !!!

- level0 : Simple GDB check
- level1 : Buffer overflow - call intern function
- level2 : Buffer Overflow - use env variable - ret2ret method
- level3 : Format string
- level4 : Format string
- level5 : Format string - call intern function
