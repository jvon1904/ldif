# J-DIF

Read from standard input and covert valid LDIF (LDAP Data Interchange Format) to JSON.

## Getting Started

To compile run `make`.

To test and example run `make example`.

## Usage

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
