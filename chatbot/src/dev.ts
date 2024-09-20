import { $ } from 'bun';

await Promise.all([$`bun start`, $`bun expose`]);
