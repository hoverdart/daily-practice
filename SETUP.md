# One-time setup

The repository is already scaffolded. To turn on automatic weekday generation, add an OpenAI API key as a GitHub Actions secret.

## 1. Add the API key

In this repository, open:

**Settings → Secrets and variables → Actions → New repository secret**

Create:

- Name: `OPENAI_API_KEY`
- Value: your OpenAI API key

Do **not** commit the key to the repository.

## 2. Optional: choose another model

Under **Settings → Secrets and variables → Actions → Variables**, optionally create:

- Name: `PRACTICE_MODEL`
- Value: an OpenAI API model name

If absent, the generator uses `gpt-6.1-sol`.

## 3. Test it manually

Open **Actions → Generate daily practice → Run workflow**.

Because Saturday and Sunday are deliberate rest days, a manual run for a weekend date will still skip generation. To test immediately, enter a weekday date such as `2026-10-05` and leave `force` enabled.

The workflow will:

1. generate three problems;
2. create starter code, tests, attempt logs, notes, and reference solutions;
3. compile/run each reference solution against its tests;
4. commit the new `practice/YYYY-MM-DD-language/` directory only if validation succeeds.

## Schedule

The workflow runs Monday through Friday at 9 AM in `America/Los_Angeles`, with daylight-saving handling built in. Saturday and Sunday generate nothing.
