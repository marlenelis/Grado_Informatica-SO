/* Jerarquia de proceso tipo 1 */

for (int i = 1; i < count; ++i)
{
	if ((childpid = fork()) ==-1)
	{
		fprintf(stderr,"Could no create child %d: %s\n",i,strerror(errno) );
		exit(-1);
	}
	if (childpid)
	{
		break;
		/* code */
	}
}

/* Jerarquia de proceso tipo 2 */

for (int i = 1; i < count; ++i)
{
	if ((childpid = fork()) ==-1)
	{
		fprintf(stderr,"Could no create child %d: %s\n",i,strerror(errno) );
		exit(-1);
	}
	if (!childpid)
	{
		break;
		/* code */
	}
}
