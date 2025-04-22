# JDIF

Read from standard input and covert valid LDIF format to JSON.

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
