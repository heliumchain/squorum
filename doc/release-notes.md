sQuorum Core version *1.0.0* is now available from:  <https://github.com/heliumchain/squorum/releases>

This is a new major version release, including various bug fixes and performance improvements.

Please report bugs using the issue tracker at github: <https://github.com/heliumchain/squorum/issues>


Mandatory Update
==============

sQuorum Core v1.0.0 is a mandatory update for all users. This release contains new consensus rules and improvements that are not backwards compatible with older versions. Users will need to update their clients before enforcement of this update goes into effect.

Update enforcement goes into effect at the following times:

    Mainnet: Saturday, September 30, 2020 4:00:00 PM GMT

Masternodes will need to be restarted once both the masternode daemon and the controller wallet have been upgraded.

How to Upgrade
==============

If you are running an older version, make a backup of your wallet.dat file and then shut down the wallet. Wait until it has completely shut down (which might take a few minutes for older versions), then run the installer to install the updated wallet.

If you had never installed the Helium Core client, then you are finished.

If you had previously been running Helium Core and used the default data folder and configuration file, you should rename the Helium data folder to sQuorum and rename the helium.conf configuration file to squorum.conf to access your old data Helium.

**Where are these data files located on my computer?**

Windows < Vista: C:\Documents and Settings\\%Username%\Application Data\Helium (sQuorum)

Windows >= Vista: C:\Users\\%Username%\AppData\Roaming\Helium (sQuorum)

Mac: ~/Library/Application Support/Helium (sQuorum)

Unix: ~/.helium (squorum)

Compatibility
==============

sQuorum Core is extensively tested on multiple operating systems using the Linux kernel, macOS 10.10+, and Windows 7 and later.

Microsoft ended support for Windows XP on [April 8th, 2014](https://www.microsoft.com/en-us/WindowsForBusiness/end-of-xp-support), No attempt is made to prevent installing or running the software on Windows XP, you can still do so at your own risk but be aware that there are known instabilities and issues. Please do not report issues about Windows XP to the issue tracker.

Apple released it's last Mountain Lion update August 13, 2015, and officially ended support on [December 14, 2015](http://news.fnal.gov/2015/10/mac-os-x-mountain-lion-10-8-end-of-life-december-14/). sQuorum Core software starting with v1.0 will no longer run on MacOS versions prior to Yosemite (10.10). Please do not report issues about MacOS versions prior to Yosemite to the issue tracker.

sQuorum Core should also work on most other Unix-like systems but is not frequently tested on them.


Notable Changes
==============

## Internal (Core) Changes

### Switch to libsecp256k1 signature verification

Here is the long overdue update for sQuorum to let go of OpenSSL in its consensus code. The rationale behind it is to avoid depending on an external and changing library where our consensus code is affected. This is security and consensus critical. sQuorum users will experience quicker block validations and sync times as block transactions are verified under libsecp256k1.

The recent [CVE-2018-0495](https://www.nccgroup.trust/us/our-research/technical-advisory-return-of-the-hidden-number-problem/) brings into question a potential vulnerability with OpenSSL (and other crypto libraries) that libsecp256k1 is not susceptible to.

### Minimum Supported MacOS Version

The minimum supported version of MacOS (OSX) has been moved from 10.8 Mountain Lion to 10.10 Yosemite. Users still running a MacOS version prior to Yosemite will need to upgrade their OS if they wish to continue using the latest version(s) of the sQuorum Core wallet.

### Fake Stake

On Janurary 22 2019, Decentralized Systems Lab out of the University of Illinois published a study entitled “[‘Fake Stake’ attacks on chain-based Proof-of-Stake cryptocurrencies](https://medium.com/@dsl_uiuc/fake-stake-attacks-on-chain-based-proof-of-stake-cryptocurrencies-b8b05723f806)”, which outlined a type of Denial of Service attack that could take place on a number of Proof of Stake based networks by exhausting a client's RAM or Disk resources.

A full report provided by PIVX developers is available on the [PIVX Website](https://pivx.org/fake-stake-official-pivx-report/), which includes additional findings, mitigation details, and resources for testing. This type of attack has no risk to users' privacy and does not affect their holdings.

### BIP65 (CHECKLOCKTIMEVERIFY) Soft-Fork

sQuorum Core v1.0.0 introduces new consensus rules for scripting pathways to support the [BIP65](https://github.com/bitcoin/bips/blob/master/bip-0065.mediawiki) standard. This is being carried out as a soft-fork in order to provide ample time for stakers to update their wallet version.

### Regression Test Suite

The RegTest network mode has been re-worked to once again allow for the generation of on-demand PoW and PoS blocks. Additionally, many of the existing functional test scripts have been adapted for use with sQuorum, and we now have a solid testing base for highly customizable tests to be written.

With this, the old `setgenerate` RPC command no longer functions in regtest mode, instead a new `generate` command has been introduced that is more suited for use in regtest mode.

### Version 2 Stake Modifier

A new 256-bit modifier for the proof of stake protocol has been defined, `CBlockIndex::nStakeModifierV2`.
It is computed at every block, by taking the hash of the modifier of previous block along with the coinstake input.
To meet the protocol, the PoS kernel must comprise the modifier of the previous block.

Changeover enforcement of this new modifier is set to occur at block `1000` for testnet and block `1000000` for mainnet.

### Block index batch writing

Block index writes are now done in a batch. This allows for less frequent disk access, meaning improved performances and less data corruption risks.

### Eliminate needless key generation

The staking process has been improved to no longer request a new (unused) key from the keypool. This should reduce wallet file size bloat as well as slightly improve staking efficiency.

## GUI Changes

### Add TOR service icon to status bar

An icon is now shown for clients that are connected and operating over the TOR network. Included is a mouse-over tooltip showing the onion address associated with the client. This icon is only shown when a connection to the TOR network can be established, and will be hidden otherwise.

### Console Security Warning

Due to an increase in social engineering attacks/scams that rely on users relaying information from console commands, a new warning message has been added to the Console window's initial welcome message.

### Optional Hiding of Orphan Stakes

The options dialog now contains a checkbox option to hide the display of orphan stakes from both the overview and transaction history sections. Further, a right-click context menu option has been introduced in the transaction history tab to achieve the same effect.

**Note:** This option only affects the visual display of orphan stakes, and will not prevent them nor remove them from the underlying wallet database.

### Receive Tab Changes

The address to be used when creating a new payment request is now automatically displayed in the form. This field is not user-editable, and will be updated as needed by the wallet.

A new button has been added below the payment request form, "Receiving Addresses", which allows for quicker access to all the known receiving addresses. This one-click button is the same as using the `File->Receiving Addresses...` menu command, and will open up the Receiving Addresses UI dialog.

Historical payment requests now also display the address used for the request in the history table. While this information was already available when clicking the "Show" button, it was an extra step that shouldn't have been necessary.

### Options Dialog Cleanup

The options/settings UI dialog has been cleaned up to no longer show settings that are wallet related when running in "disable wallet" (`-disablewallet`) mode.

### Removal of zero-fee transaction option

The long term viability of acceptable zero-fee transaction conditions is in need of review. As such, we are temporarily disabling the ability to create zero-fee transactions.

### Removal of zerocoin section from GUI

sQuorum does not support the use of zerocoin transactions, and this section has been removed from the GUI and wallet options.

### Show latest block hash and datadir information tab

A QoL addition has been made to the Information tab of the UI's console window, which adds the display of both the current data directory and the latest block hash seen by the client.

## RPC Changes

### Backupwallet Sanity

The `backupwallet` RPC command no longer allows for overwriting the currently in use wallet.dat file. This was done to avoid potential file corruption caused by multiple conflicting file access operations.

### Getreceivedbyaddress Update

When calling `getreceivedbyaddress` with a non-wallet address, return a proper error code/message instead of just `0`

### Validateaddress More Verbosity

`validateaddress` now has the ability to return more (non-critical or identifying) details about P2SH (multisig) addresses by removing the needless check against ISMINE_NO.

### Getblock & Getblockheader

A minor change to these two RPC commands to now display the `mediantime`, used primarialy during functional tests.

### Getwalletinfo

The `getwalletinfo` RPC command now outputs the configured transaction fee (`paytxfee` field).

### Removal of Deprecated Commands

The `masternode` and `mnbudget` RPC commands, which were marked as deprecated in PIVX Core v2.3.1 (September 19, 2017), have been completely removed from sQuorum Core.

Several new commands were added in PIVX Core v2.3.1 to replace the two aforementioned commands, reference the [v2.3.1 Release Notes](https://github.com/heliumchain/squorum/blob/master/doc/release-notes/release-notes-2.3.1.md#rpc-changes) for further details.

### New `getblockindexstats` Command

A new RPC command (`getblockindexstats`) has been introduced which serves the purpose of obtaining statistical information on a range of blocks. The information returned is as follows:
  * transaction count (not including coinbase/coinstake txes)
  * transaction count (including coinbase/coinstake txes)
  * zSQR per-denom mint count
  * zSQR per-denom spend count
  * total transaction bytes
  * total fees in block range
  * average fee per kB

Command Reference:
```$xslt
getblockindexstats height range ( fFeeOnly )
nReturns aggregated BlockIndex data for blocks
height, height+1, height+2, ..., height+range-1]

nArguments:
1. height             (numeric, required) block height where the search starts.
2. range              (numeric, required) number of blocks to include.
3. fFeeOnly           (boolean, optional, default=False) return only fee info.
```
Result:
```
{
  first_block: x,              (integer) First counted block
  last_block: x,               (integer) Last counted block
  txcount: xxxxx,              (numeric) tx count (excluding coinbase/coinstake)
  txcount_all: xxxxx,          (numeric) tx count (including coinbase/coinstake)
  mintcount: {              [if fFeeOnly=False]
        denom_1: xxxx,         (numeric) number of mints of denom_1 occurred over the block range
        denom_5: xxxx,         (numeric) number of mints of denom_5 occurred over the block range
         ...                    ... number of mints of other denominations: ..., 10, 50, 100, 500, 1000, 5000
  },
  spendcount: {             [if fFeeOnly=False]
        denom_1: xxxx,         (numeric) number of spends of denom_1 occurred over the block range
        denom_5: xxxx,         (numeric) number of spends of denom_5 occurred over the block range
         ...                    ... number of spends of other denominations: ..., 10, 50, 100, 500, 1000, 5000
  },
  pubspendcount: {          [if fFeeOnly=False]
        denom_1: xxxx,         (numeric) number of PUBLIC spends of denom_1 occurred over the block range
        denom_5: xxxx,         (numeric) number of PUBLIC spends of denom_5 occurred over the block range
         ...                   ... number of PUBLIC spends of other denominations: ..., 10, 50, 100, 500, 1000, 5000
  },
  txbytes: xxxxx,              (numeric) Sum of the size of all txes (zSQR excluded) over block range
  ttlfee: xxxxx,               (numeric) Sum of the fee amount of all txes (zSQR mints excluded) over block range
  ttlfee_all: xxxxx,           (numeric) Sum of the fee amount of all txes (zSQR mints included) over block range
  feeperkb: xxxxx,             (numeric) Average fee per kb (excluding zc txes)
}
```

### Require valid URL scheme when preparing/submitting a proposal

The `preparebudget` and `submitbudget` RPC commands now require the inclusion of a canonical URL scheme as part of their `url` parameter. Strings that don't include either `http://` or `https://` will be rejected.

The 64 character limit for the `url` field is inclusive of this change, so the use of a URL shortening service may be needed.

## Testing Suite Changes

### Functional testing readability

Several changes have been introduced to the travis script in order to make the output more readable. Specifically it now lists tests left to run and prints the output of failing scripts.

## Build System Changes

### Completely Disallow Qt4

Compiling the sQuorum Core wallet against Qt4 hasn't been supported for quite some time now, but the build system still recognized Qt4 as a valid option if Qt5 couldn't be found. This has now been remedied and Qt4 will no longer be considered valid during the `configure` pre-compilation phase.

### Further OpenSSL Deprecation

Up until now, the zerocoin library relied exclusively on OpenSSL for it's bignum implementation. This has now been changed with the introduction of GMP as an arithmetic operator and the bignum implementation has now been redesigned around GMP. Users can still opt to use OpenSSL for bignum by passing `--with-zerocoin-bignum=openssl` to the `configure` script, however such configuration is now deprecated.

**Note:** This change introduces a new dependency on GMP (libgmp) by default.

### RISC-V Support

Support for the new RISC-V 64bit processors has been added, though still experimental. Pre-compiled binaries for this CPU architecture are available for linux, and users can self-compile using gitian, depends, or an appropriate host system natively.

### New Gitian Build Script

The previous `gitian-build.sh` shell script has been replaced with a more feature rich python version; `gitian-build.py`. This script now supports the use of a docker container in addition to LXC or KVM virtualization, as well as the ability to build against a pull request by number.

### New Architectures for Depends

The depends system has new added support for the `s390x` and `ppc64el` architectures. This is done in order to support the future integration with [Snapcraft](https://www.snapcraft.io), as well as to support any developers who may use systems based on such architectures.

### Basic CMake Support

While the existing Autotools based build system is our standard build system, and will continue to be so, we have added basic support for compiling with CMake on macOS and linux systems.

This is intended to be used in conjunction with IDEs like CLion (which relies heavily on CMake) in order to streamline the development process. Developers can now use, for example, CLion's internal debugger and profiling tools.

Note that it is still required to have relevant dependencies installed on the system for this to function properly.

### OpenSSL configure information

When the configure step fails because of an unsupported OpenSSL (or other library), it now displays more information on using an override flag to compile anyways. The long term plan is to ensure that the consensus code doesn't depend on OpenSSL in any way and then remove this configure step and related override flag.


As well as everyone that helped translating on [Transifex](https://www.transifex.com/squorum-project/squorum-wallet/), the QA team during Testing and the Node hosts supporting our Testnet.
