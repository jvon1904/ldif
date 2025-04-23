# J-DIF

Read from standard input and covert valid LDIF format to JSON.

LDIF - LDAP Data Interchange Format

```bash
$ echo 'hello: world' | jdif 
{"hello": "world"}
```

Then, you can combine this with a library like `jq`.

```bash
$ echo 'hello: world' | jdif | jq
{
  "hello": "world"
}
```

This is created to be combined with a uitlity like `ldapsearch`.

```bash
$ ldapsearch ... | jdif
```
